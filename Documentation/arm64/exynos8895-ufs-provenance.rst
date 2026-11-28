Exynos8895 UFS calibration provenance
====================================

Status: NOT APPROVED. User supplied the archive but explicitly withheld
provenance approval. Calibration commits must not be merged. DT stays disabled.

Archive: SM-G950F_PP_Opensource.zip
SHA-256: 7a179801b8927fb603690c4bf9bcfb7d2a35fe639f46d997ba43c092a64c80b3
Inner Kernel.tar.gz SHA-256:
f1a4c62c8f400b95cb221391b6f48dbbc9e7c7b7a6b2c778d26da20c75e3fa23

Makefile lines 1-4: VERSION=4, PATCHLEVEL=4, SUBLEVEL=111, EXTRAVERSION empty.
README_Kernel.txt: ANDROID_MAJOR_VERSION=p, ARCH=arm64,
make exynos8895-dreamlte_defconfig, GCC 4.9.
ZIP entry timestamps: 2022-07-21 (not proof of publication).

File-level evidence (paths relative to Kernel.tar.gz):

* drivers/scsi/ufs/ufs-exynos.c and drivers/scsi/ufs/ufs-exynos.h:
  line 4: Copyright (C) 2013-2014 Samsung Electronics Co., Ltd.
  lines 6-9: GPL version 2 or any later version; no SPDX in header.
  SHA-256 C: 5f29c3844ca5f5adc435bde590d9f4cb82a9fb622e630fcb0cc0bd822cecd195
  SHA-256 H: b73fd887fbe13bad855a20ca2a060cfd29d79cfeddf456371bf544cecf12396e
* arch/arm64/boot/dts/exynos/exynos8895.dtsi:
  line 4: Copyright (c) 2014 Samsung Electronics Co., Ltd.
  line 5: http://www.samsung.com
  lines 11-13: GNU General Public License version 2; no SPDX in header.
  SHA-256: 52b5eea791f22f9ca3dadd8dc6dbcd0d2e87734b49b2cff7c75966f3f63f948e
* COPYING: GPL version 2, June 1991; FSF copyright 1989, 1991.

These internal notices and model-specific build instructions support Samsung
origin but do not authenticate the archive against an official download.
Independent origin verification remains pending. Fork provenance is not approved.
Existing calibration changes require a separate line-by-line source audit.
Build and physical boot not verified.
