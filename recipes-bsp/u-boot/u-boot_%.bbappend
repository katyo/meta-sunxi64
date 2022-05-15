FILESEXTRAPATHS:prepend:sunxi := "${THISDIR}/files:"

DEPENDS:append:sunxi64 = " tf-a"

#COMPATIBLE_MACHINE:sunxi = "(sun4i|sun5i|sun7i|sun8i)"
COMPATIBLE_MACHINE:sunxi64 = "(sun50i)"

#DEFAULT_PREFERENCE:sun4i = "1"
#DEFAULT_PREFERENCE:sun5i = "1"
#DEFAULT_PREFERENCE:sun7i = "1"
#DEFAULT_PREFERENCE:sun8i = "1"
DEFAULT_PREFERENCE:sun50i = "1"

SRC_URI:append:sunxi = " file://boot.cmd"
SRC_URI:append:sun50iw6 = " file://0003-add-orange-pi-3-lts-support.patch"
SRC_URI:append:sun50iw9 = " file://0001-Adding-h616-THS-workaround.patch file://0002-sunxi-H616-GPU-enable-hack.patch"

UBOOT_ENV_SUFFIX:sunxi = "scr"
UBOOT_ENV:sunxi = "boot"

EXTRA_OEMAKE:append:sunxi = ' HOSTLDSHARED="${BUILD_CC} -shared ${BUILD_LDFLAGS} ${BUILD_CFLAGS}"'
EXTRA_OEMAKE:append:sunxi64 = " BL31=${DEPLOY_DIR_IMAGE}/bl31.bin"

do_compile:sunxi64[depends] += " tf-a:do_deploy"

do_compile:append:sunxi() {
    ${B}/tools/mkimage -C none -A arm -T script -d ${WORKDIR}/boot.cmd ${WORKDIR}/${UBOOT_ENV_BINARY}
}
