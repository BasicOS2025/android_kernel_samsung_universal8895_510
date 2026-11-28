Dreamlte boot diagnostics audit
===============================

Baseline: ef0274d1b0dfd567c4f3d5a3d05d16ff2385286a.
PR #1 merged; PR #2 draft, provenance NOT APPROVED.

UART
----

The baseline dreamlte DTS has no serial node or stdout-path. The defconfig
selects PL011 and tty0, not Samsung serial. Keep PL011 for QEMU.
The existing clk-exynos8895.c provides CLK_GOUT_PERIC0_UART_DBG_PCLK
and CLK_GOUT_PERIC0_UART_DBG_EXT_UCLK. The target binding
Documentation/devicetree/bindings/serial/samsung_uart.yaml lists
samsung,exynos4210-uart with uart and clk_uart_baud0 clock names.
This is a candidate interface, not proof of Exynos8895 compatibility.
Verify the actual UART register range, IRQ, FIFO, pin routing and
bootloader clock state from an authenticated source before adding a node.
Do not enable a DT node or change stdout-path in this draft.

Persistent logs
---------------

The board DTS reserves ramoops at 0x92000000, size 0x8000, with
record-size and console-size both 0x4000. This consumes the region;
no separate pmsg capacity is configured despite CONFIG_PSTORE_PMSG=y.
CONFIG_PSTORE, CONFIG_PSTORE_CONSOLE and CONFIG_PSTORE_RAM are present.
Do not enlarge or relocate the reservation without firmware memory-map
verification. Absence of no-map is not evidence of a fault.
Verify actual warm-reset retention and recovery access to /sys/fs/pstore
on hardware. Early crashes before ramoops probe may not be recorded.

Validation: static inspection only. No build or physical boot performed.
No calibration changes, DT enablement or defconfig changes in this draft.
