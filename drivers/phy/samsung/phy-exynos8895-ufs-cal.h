/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * PMA calibration data adapted from exynos8895.dtsi in
 * SM-G950F_PP_Opensource.zip.
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Byte offsets, not Exynos7 APB word offsets. HS gear-specific
 * entries are valid only for two-lane operation.
 * See Documentation/arm64/exynos8895-ufs-provenance.rst.
 */
#ifndef _PHY_EXYNOS8895_UFS_CAL_
#define _PHY_EXYNOS8895_UFS_CAL_

#define EXYNOS8895_LANE_STRIDE 0x140
#define EXYNOS8895_CDR_REG 0x1fc
#define EXYNOS8895_CDR_MASK BIT(0)
#define EXYNOS8895_CDR_TIMEOUT_US 100000
#define E8895_COM(o, v) { .off_0 = (o), .val = (v), .id = PHY_COMN_BLK }
#define E8895_TR(o, v) { .off_0 = (o), .off_1 = (o) + EXYNOS8895_LANE_STRIDE, .val = (v), .id = PHY_TRSV_BLK }

static const struct samsung_ufs_phy_cfg exynos8895_pma_init[] = {
	E8895_COM(0x8c, 0x80), E8895_COM(0x74, 0x10),
	E8895_TR(0x110, 0xb5), E8895_TR(0x134, 0x43),
	E8895_TR(0x16c, 0x20), E8895_TR(0x178, 0xc0),
	E8895_TR(0xe0, 0x12), E8895_TR(0x164, 0x58),
	E8895_COM(0x8c, 0xc0), E8895_COM(0x8c, 0x00),
	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg exynos8895_pma_pwm[] = {
	E8895_TR(0xc8, 0x40), E8895_TR(0xf0, 0x77),
	E8895_TR(0x120, 0x80), E8895_TR(0x128, 0x00),
	E8895_TR(0x12c, 0x00), E8895_TR(0x134, 0x43),
	END_UFS_PHY_CFG,
};

/* HS rate A and B share the same PMA values in the source. */
#define E8895_HS_COMMON E8895_TR(0xc8, 0xbc), E8895_TR(0xf0, 0x7f), E8895_TR(0x120, 0xc0)
#define E8895_HS_TAIL E8895_TR(0x108, 0x5d), E8895_TR(0x10c, 0x90), END_UFS_PHY_CFG
static const struct samsung_ufs_phy_cfg exynos8895_pma_hs_single[] = {
	E8895_HS_COMMON, E8895_HS_TAIL,
};
static const struct samsung_ufs_phy_cfg exynos8895_pma_hs_g1_l2[] = {
	E8895_HS_COMMON, E8895_TR(0x128, 0x08), E8895_TR(0x12c, 0),
	E8895_TR(0x134, 0xd3), E8895_HS_TAIL,
};
static const struct samsung_ufs_phy_cfg exynos8895_pma_hs_g2_l2[] = {
	E8895_HS_COMMON, E8895_TR(0x128, 0x02), E8895_TR(0x12c, 0),
	E8895_TR(0x134, 0x73), E8895_HS_TAIL,
};
static const struct samsung_ufs_phy_cfg exynos8895_pma_hs_g3_l2[] = {
	E8895_HS_COMMON, E8895_TR(0x128, 0x00), E8895_TR(0x12c, 0),
	E8895_TR(0x134, 0x63), E8895_HS_TAIL,
};
#undef E8895_HS_COMMON
#undef E8895_HS_TAIL
#undef E8895_COM
#undef E8895_TR
#endif
