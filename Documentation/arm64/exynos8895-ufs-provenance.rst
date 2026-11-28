Exynos8895 UFS calibration provenance
====================================

Status: NOT APPROVED. User supplied archive; permission to merge calibration
has not been granted. Independent Samsung download origin not verified.

Archive: SM-G950F_PP_Opensource.zip
SHA-256: 7a179801b8927fb603690c4bf9bcfb7d2a35fe639f46d997ba43c092a64c80b3
ZIP entries dated 2022-07-21; Kernel.tar.gz, Platform.tar.gz,
README_Kernel.txt, README_Platform.txt.
Kernel Makefile: VERSION=4 PATCHLEVEL=4 SUBLEVEL=111.
README_Kernel.txt: ANDROID_MAJOR_VERSION=p, ARCH=arm64,
make exynos8895-dreamlte_defconfig.

Paths inside Kernel.tar.gz (SHA-256):
* arch/arm64/boot/dts/exynos/exynos8895.dtsi
  52b5eea791f22f9ca3dadd8dc6dbcd0d2e87734b49b2cff7c75966f3f63f948e
  Line 4: Copyright (c) 2014 Samsung Electronics Co., Ltd.
  Lines 11-13: GNU General Public License version 2.
* drivers/scsi/ufs/ufs-exynos.c
  5f29c3844ca5f5adc435bde590d9f4cb82a9fb622e630fcb0cc0bd822cecd195
  Line 4: Copyright (C) 2013-2014 Samsung Electronics Co., Ltd.
  Lines 6-9: GPL version 2 or any later version.
* drivers/scsi/ufs/ufs-exynos.h
  b73fd887fbe13bad855a20ca2a060cfd29d79cfeddf456371bf544cecf12396e
  Same copyright and license as .c.
No SPDX identifier in these original headers; license identifiers above
are interpretations of the notices. Root COPYING is GPL v2.
Samsung notices and model-specific build instructions support attribution
but do not authenticate the archive distribution chain.

Target calibration header declares GPL-2.0-only and Samsung 2014 copyright.
Target PHY C/header declare GPL-2.0-only and Samsung 2020 copyright.
Target drivers/scsi/ufs/ufs-exynos.c: SPDX GPL-2.0-only,
Copyright (C) 2014-2015 Samsung Electronics Co., Ltd.
Source values: header line 465 stride 0x140; DTS lines 1031/1035 CDR
0x1fc mask 0x01. Hardware validity not tested. Full table fidelity and
ordering require review. No DT enablement or merge before approval.
Build result pending; physical boot not tested.
