DESCRIPTION = "ARM Trusted Firmware Allwinner"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

SRC_URI = "git://github.com/ARM-software/arm-trusted-firmware.git;protocol=https;nobranch=1"
SRCPV = "v${PV}"
SRCREV = "35f4c7295bafeb32c8bcbdfb6a3f2e74a57e732b"

SRC_URI:append = " file://0002-Quick-fix-for-bl31.elf-has-a-LOAD-segment-with-RWX-p.patch"
SRC_URI:append:sun50iw6 = " file://0001-Fix-reset-issue-on-H6-by-using-R_WDOG.patch"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(sunxi64)"

PLATFORM:sun50iw6 = "sun50i_h6"
PLATFORM:sun50iw9 = "sun50i_h616"

LDFLAGS[unexport] = "1"

do_compile() {
    oe_runmake -C ${S} BUILD_BASE=${B} \
      CROSS_COMPILE=${TARGET_PREFIX} \
      PLAT=${PLATFORM} \
      bl31 \
      all
}

do_install() {
    install -D -p -m 0644 ${B}/${PLATFORM}/release/bl31.bin ${DEPLOY_DIR_IMAGE}/bl31.bin
}
