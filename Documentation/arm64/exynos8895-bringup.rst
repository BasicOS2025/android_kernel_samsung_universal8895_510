Exynos8895 dreamlte bring-up
============================

Experimental CPU frequency targets (not enabled)
------------------------------------------------

* Mongoose M2: 2400000 kHz, stock target 2300000 kHz.
* Cortex-A53: 1900000 kHz, stock target 1700000 kHz.

Do not expose these frequencies until the SoC clock/PLL and DVFS drivers,
verified OPP voltages and thermal cooling bindings are operational.
Keep stock limits as defaults; do not bypass thermal protection.
Validate each cluster independently and revert on instability.

Storage bring-up requires verified Exynos8895 UFS host, PHY calibration,
clock and regulator bindings. Generic Exynos UFS configuration alone is
not hardware support. Verify enumeration before any write tests.

Android 17 validation requires a real device boot and userspace tests;
configuration selections alone are not evidence of compatibility.
