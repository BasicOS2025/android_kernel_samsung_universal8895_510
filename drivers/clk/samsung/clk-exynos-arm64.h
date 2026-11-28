/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __CLK_EXYNOS_ARM64_H
#define __CLK_EXYNOS_ARM64_H
#include "clk.h"
void exynos_arm64_register_cmu(struct device *dev, struct device_node *np,
		const struct samsung_cmu_info *cmu);
#endif
