Exynos8895 UFS calibration provenance
====================================

User-supplied SM-G950F_PP_Opensource.zip, SHA-256:
7a179801b8927fb603690c4bf9bcfb7d2a35fe639f46d997ba43c092a64c80b3

Kernel.tar.gz: arch/arm64/boot/dts/exynos/exynos8895.dtsi,
Copyright (c) 2014 Samsung Electronics Co., Ltd., GPL version 2.
User approved integration from this archive; independent download origin
not verified. No third-party fork code used.

PMA byte stride 0x140; HS CDR address 0x1fc, mask 0x01.
Vendor drivers/scsi/ufs/ufs-exynos.c polls lane zero for 100 ms.
HS gear-specific entries apply to two lanes only. PCS, UniPro and PMA
operations must retain ordering. Build and physical boot not tested.
