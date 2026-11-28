# Exynos 8895 Linux 5.10 bring-up

This public Android Common Kernel fork starts from Linux 5.10.245,
`android13-5.10` at `9536d991bb596a507f46aafe6b5f64fe9e599e78`.
The development target is the first Android 17 release. AOSP's Android 17
QPR1 and later releases require a newer Android Common Kernel branch.

The Galaxy S8 (SM-G950F, `dreamlte`) is the first target. Its minimal
device tree describes the CPU topology, interrupt controller, timer,
RAM, bootloader splash framebuffer and persistent crash-log reservation.
The defconfig enables Binder/BinderFS, cgroup BPF and JIT, namespaces,
SELinux, ext4/F2FS encryption and pstore. The IPv4 and IPv6 x_tables
filter tables and the built-in xt_bpf match support Android network
filtering.

## LineageOS Z3S reference

The LineageOS 24.0 Galaxy S20 Ultra kernel uses Linux 4.19.325 with
substantial backports. Its universal9830-common device tree sets
`ro.bpf.kver_override=5.10.239` for the Android BPF loader. This fork
uses the native 5.10.245 BPF implementation, with no corresponding
ROM property configured here. The reference informed BinderFS,
cgroup BPF and xt_bpf configuration.

- [Pinned universal9830 kernel configuration](https://github.com/LineageOS/android_kernel_samsung_universal9830/blob/97369af7bbd66581d3e993fea083f3eed02d3c20/arch/arm64/configs/exynos9830_defconfig)
- [Pinned universal9830-common BPF property](https://github.com/LineageOS/android_device_samsung_universal9830-common/blob/f8db0251719ed30b92ce6765611af5c4d1826ead/product.prop)

## Build the ARM64 Image and Galaxy S8 DTB

Use an AArch64 Linux toolchain and the standard Linux kernel build
dependencies, including make, bc, flex, bison and OpenSSL headers.

```sh
make O=out ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- exynos8895_dreamlte_defconfig
make O=out ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- \
    KCFLAGS=-Wno-error -j"$(nproc)" Image exynos/exynos8895-dreamlte.dtb
```

The outputs are `out/arch/arm64/boot/Image` and
`out/arch/arm64/boot/dts/exynos/exynos8895-dreamlte.dtb`.
These are raw build outputs for bring-up. UFS, power management, full
display, vendor HALs and physical Android boot validation are pending.

The first build passed all 64 requested Kconfig selections. The same
ARM64 Image booted a test initramfs under QEMU virt and passed BPF
object naming, cgroup socket-create enforcement and detach, and IPv4
and IPv6 xt_bpf registration. That test used QEMU's virtual DTB.
The compiled dreamlte DTB was checked separately.

## Galaxy S8 LineageOS boot path

The dreamlte DTB now carries the Samsung DTBH model IDs from the
downstream Galaxy S8 EUR rev10 device tree. The existing LineageOS
device packer accepted one DTBH entry for chip 8895 and hardware
revisions 10–255. The host validator accepted the 2048-byte boot
image page layout and Samsung load addresses with this kernel and
a diagnostic initramfs. The diagnostic archive does not include
the LineageOS first-stage ramdisk or Samsung fstab.

The pinned LineageOS device fstab needs
`/dev/block/platform/11120000.ufs/by-name/SYSTEM` at first-stage
mount. The 5.10 Exynos UFS driver now includes an experimental Exynos8895 host
match and FSYS0 coherency configuration. Complete the controller and PHY,
clocks and regulators, and verify the Android block-device path
on hardware before switching the ROM manifest to this kernel.
Check that the physical bootloader hands control to the 5.10
Image and that the ramoops records survive a warm reset.

- [Existing Samsung boot packer](https://github.com/BasicOS2025/android_device_samsung_universal8895-common/blob/ef490e1abfa212ab2f0c562101fd440df839eb46/tools/mkbootimg.mk)
- [LineageOS first-stage fstab](https://github.com/BasicOS2025/android_device_samsung_universal8895-common/blob/ef490e1abfa212ab2f0c562101fd440df839eb46/ramdisk/etc/fstab.samsungexynos8895)

- [Android Common Kernel support matrix](https://source.android.com/docs/core/architecture/kernel/android-common)
- [Reference Galaxy S8 device tree](https://android.googlesource.com/kernel/common/+/76bdb627cab87dfa1d901810e22ee7fae6d3dc89/arch/arm64/boot/dts/exynos/exynos8895-dreamlte.dts)

---

# How do I submit patches to Android Common Kernels

1. BEST: Make all of your changes to upstream Linux. If appropriate, backport to the stable releases.
   These patches will be merged automatically in the corresponding common kernels. If the patch is already
   in upstream Linux, post a backport of the patch that conforms to the patch requirements below.
   - Do not send patches upstream that contain only symbol exports. To be considered for upstream Linux,
additions of `EXPORT_SYMBOL_GPL()` require an in-tree modular driver that uses the symbol -- so include
the new driver or changes to an existing driver in the same patchset as the export.
   - When sending patches upstream, the commit message must contain a clear case for why the patch
is needed and beneficial to the community. Enabling out-of-tree drivers or functionality is not
not a persuasive case.

2. LESS GOOD: Develop your patches out-of-tree (from an upstream Linux point-of-view). Unless these are
   fixing an Android-specific bug, these are very unlikely to be accepted unless they have been
   coordinated with kernel-team@android.com. If you want to proceed, post a patch that conforms to the
   patch requirements below.

# Common Kernel patch requirements

- All patches must conform to the Linux kernel coding standards and pass `script/checkpatch.pl`
- Patches shall not break gki_defconfig or allmodconfig builds for arm, arm64, x86, x86_64 architectures
(see  https://source.android.com/setup/build/building-kernels)
- If the patch is not merged from an upstream branch, the subject must be tagged with the type of patch:
`UPSTREAM:`, `BACKPORT:`, `FROMGIT:`, `FROMLIST:`, or `ANDROID:`.
- All patches must have a `Change-Id:` tag (see https://gerrit-review.googlesource.com/Documentation/user-changeid.html)
- If an Android bug has been assigned, there must be a `Bug:` tag.
- All patches must have a `Signed-off-by:` tag by the author and the submitter

Additional requirements are listed below based on patch type

## Requirements for backports from mainline Linux: `UPSTREAM:`, `BACKPORT:`

- If the patch is a cherry-pick from Linux mainline with no changes at all
    - tag the patch subject with `UPSTREAM:`.
    - add upstream commit information with a `(cherry picked from commit ...)` line
    - Example:
        - if the upstream commit message is
```
        important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>
```
>- then Joe Smith would upload the patch for the common kernel as
```
        UPSTREAM: important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>

        Bug: 135791357
        Change-Id: I4caaaa566ea080fa148c5e768bb1a0b6f7201c01
        (cherry picked from commit c31e73121f4c1ec41143423ac6ce3ce6dafdcec1)
        Signed-off-by: Joe Smith <joe.smith@foo.org>
```

- If the patch requires any changes from the upstream version, tag the patch with `BACKPORT:`
instead of `UPSTREAM:`.
    - use the same tags as `UPSTREAM:`
    - add comments about the changes under the `(cherry picked from commit ...)` line
    - Example:
```
        BACKPORT: important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>

        Bug: 135791357
        Change-Id: I4caaaa566ea080fa148c5e768bb1a0b6f7201c01
        (cherry picked from commit c31e73121f4c1ec41143423ac6ce3ce6dafdcec1)
        [joe: Resolved minor conflict in drivers/foo/bar.c ]
        Signed-off-by: Joe Smith <joe.smith@foo.org>
```

## Requirements for other backports: `FROMGIT:`, `FROMLIST:`,

- If the patch has been merged into an upstream maintainer tree, but has not yet
been merged into Linux mainline
    - tag the patch subject with `FROMGIT:`
    - add info on where the patch came from as `(cherry picked from commit <sha1> <repo> <branch>)`. This
must be a stable maintainer branch (not rebased, so don't use `linux-next` for example).
    - if changes were required, use `BACKPORT: FROMGIT:`
    - Example:
        - if the commit message in the maintainer tree is
```
        important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>
```
>- then Joe Smith would upload the patch for the common kernel as
```
        FROMGIT: important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>

        Bug: 135791357
        (cherry picked from commit 878a2fd9de10b03d11d2f622250285c7e63deace
         https://git.kernel.org/pub/scm/linux/kernel/git/foo/bar.git test-branch)
        Change-Id: I4caaaa566ea080fa148c5e768bb1a0b6f7201c01
        Signed-off-by: Joe Smith <joe.smith@foo.org>
```


- If the patch has been submitted to LKML, but not accepted into any maintainer tree
    - tag the patch subject with `FROMLIST:`
    - add a `Link:` tag with a link to the submittal on lore.kernel.org
    - add a `Bug:` tag with the Android bug (required for patches not accepted into
a maintainer tree)
    - if changes were required, use `BACKPORT: FROMLIST:`
    - Example:
```
        FROMLIST: important patch from upstream

        This is the detailed description of the important patch

        Signed-off-by: Fred Jones <fred.jones@foo.org>

        Bug: 135791357
        Link: https://lore.kernel.org/lkml/20190619171517.GA17557@someone.com/
        Change-Id: I4caaaa566ea080fa148c5e768bb1a0b6f7201c01
        Signed-off-by: Joe Smith <joe.smith@foo.org>
```

## Requirements for Android-specific patches: `ANDROID:`

- If the patch is fixing a bug to Android-specific code
    - tag the patch subject with `ANDROID:`
    - add a `Fixes:` tag that cites the patch with the bug
    - Example:
```
        ANDROID: fix android-specific bug in foobar.c

        This is the detailed description of the important fix

        Fixes: 1234abcd2468 ("foobar: add cool feature")
        Change-Id: I4caaaa566ea080fa148c5e768bb1a0b6f7201c01
        Signed-off-by: Joe Smith <joe.smith@foo.org>
```

- If the patch is a new feature
    - tag the patch subject with `ANDROID:`
    - add a `Bug:` tag with the Android bug (required for android-specific features)

