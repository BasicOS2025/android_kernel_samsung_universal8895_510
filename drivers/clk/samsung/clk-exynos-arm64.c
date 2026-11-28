// SPDX-License-Identifier: GPL-2.0-only
/*
 * Based on Exynos ARM64 CMU helpers by Sam Protsenko and David Virag,
 * Copyright (C) 2021 Linaro Ltd.
 * Linux 5.10 bring-up: non-runtime-PM registration path only.
 */
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include "clk-exynos-arm64.h"

#define GATE_MANUAL BIT(20)
#define GATE_ENABLE_HWACG BIT(28)

int __init exynos_arm64_register_cmu(struct device *dev,
		struct device_node *np, const struct samsung_cmu_info *cmu)
{
	struct clk *bus;
	struct samsung_clk_provider *ctx;
	void __iomem *base;
	unsigned int i;
	int ret;

	if (cmu->clk_name) {
		bus = dev ? clk_get(dev, cmu->clk_name) :
			of_clk_get_by_name(np, cmu->clk_name);
		if (IS_ERR(bus)) {
			pr_err("%pOF: CMU bus clock unavailable: %ld\n",
			       np, PTR_ERR(bus));
			return PTR_ERR(bus);
		}
		ret = clk_prepare_enable(bus);
		if (ret) {
			clk_put(bus);
			pr_err("%pOF: CMU bus enable failed: %d\n", np, ret);
			return ret;
		}
		/* CMU register access requires this clock for its lifetime. */
	}

	base = of_iomap(np, 0);
	if (!base) {
		pr_err("%pOF: CMU register mapping failed\n", np);
		if (cmu->clk_name) {
			clk_disable_unprepare(bus);
			clk_put(bus);
		}
		return -ENOMEM;
	}
	for (i = 0; i < cmu->nr_clk_regs; i++) {
		unsigned long off = cmu->clk_regs[i];
		u32 val;

		if (off < 0x2000 || off > 0x2fff)
			continue;
		val = readl(base + off);
		val |= GATE_MANUAL;
		val &= ~GATE_ENABLE_HWACG;
		writel(val, base + off);
	}
	iounmap(base);
	ctx = samsung_cmu_register_one(np, cmu);
	return ctx ? 0 : -ENOMEM;
}
