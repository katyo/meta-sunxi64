SECTION = "kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
COMPATIBLE_MACHINE = "(sun50i)"

inherit kernel

require linux.inc

# Since we're not using git, this doesn't make a difference, but we need to fill
# in something or kernel-yocto.bbclass will fail.
KBRANCH ?= "master"

DEPENDS += "rsync-native"

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"

KERNEL_EXTRA_ARGS += "LOADADDR=${UBOOT_ENTRYPOINT}"

S = "${WORKDIR}/linux-${PV}"

SRC_URI = "https://www.kernel.org/pub/linux/kernel/v5.x/linux-${PV}.tar.xz"
#SRC_URI = "git://github.com/katyo/linux.git;protocol=https"

SRC_URI:append:sunxi = " https://github.com/katyo/linux/compare/v${PV}...v${PV}-sunxi64.patch;name=sunxi-patches"

SRC_URI:append = " file://defconfig"

# H6 & H616
do_configure:prepend:sun50i() {
    kernel_conf_var ARCH_SUNXI y
    kernel_conf_var ARM y
    kernel_conf_var ARM_ARCH_TIMER y
    kernel_conf_var ARM_GIC y
    kernel_conf_var ARM_PSCI_FW y
    kernel_conf_var ARM_SCPI_PROTOCOL y
    kernel_conf_var DMADEVICES y
    kernel_conf_var DMA_SUN6I y
    kernel_conf_var DUMP_REG y
    kernel_conf_var DWMAC_SUN8I y
    kernel_conf_var ETHERNET y
    kernel_conf_var GENERIC_PHY y
    kernel_conf_var I2C y
    kernel_conf_var I2C_MV64XXX y
    kernel_conf_var IR_SUNXI y
    kernel_conf_var MAILBOX y
    kernel_conf_var MMC y
    kernel_conf_var MMC_SUNXI y
    kernel_conf_var NET_VENDOR_STMICRO y
    kernel_conf_var NVMEM y
    kernel_conf_var NVMEM_SUNXI_SID y
    kernel_conf_var OF y
    kernel_conf_var PHY_SUN4I_USB y
    kernel_conf_var PINCTRL y
    kernel_conf_var PINCTRL_SUNXI y
    kernel_conf_var PINCTRL_SUN8I_H3_R n
    kernel_conf_var PINCTRL_SUN50I_A64 n
    kernel_conf_var PINCTRL_SUN50I_A64_R n
    kernel_conf_var PINCTRL_SUN50I_A100 n
    kernel_conf_var PINCTRL_SUN50I_A100_R n
    kernel_conf_var PINCTRL_SUN50I_H5 n
    kernel_conf_var RTC_DRV_SUN6I y
    kernel_conf_var RTC_LIB y
    kernel_conf_var SERIAL_8250 y
    kernel_conf_var SERIAL_8250_DW y
    kernel_conf_var SND y
    kernel_conf_var SND_SOC y
    kernel_conf_var SPI y
    kernel_conf_var SPI_SUN6I y
    kernel_conf_var STAGING y
    kernel_conf_var STAGING_MEDIA y
    kernel_conf_var STMMAC_ETH y
    kernel_conf_var STMMAC_PLATFORM y
    kernel_conf_var SUN50I_A64_CCU n
    kernel_conf_var SUN50I_A100_CCU n
    kernel_conf_var SUN50I_A100_R_CCU n
    kernel_conf_var SUN8I_H3_CCU n
    kernel_conf_var SUN8I_R_CCU n
    kernel_conf_var SUN50I_H6_R_CCU y
    kernel_conf_var SUN6I_RTC_CCU y
    kernel_conf_var SUN8I_THERMAL y
    kernel_conf_var SUNXI_ADDR_MGMT y
    kernel_conf_var SUNXI_RSB y
    kernel_conf_var SUNXI_SRAM y
    kernel_conf_var SUNXI_SYS_INFO y
    kernel_conf_var SUNXI_WATCHDOG y
    kernel_conf_var THERMAL y
    kernel_conf_var USB y
    kernel_conf_var USB_DWC3 y
    kernel_conf_var USB_EHCI_HCD y
    kernel_conf_var USB_EHCI_HCD_PLATFORM y
    kernel_conf_var USB_MUSB_HDRC y
    kernel_conf_var USB_MUSB_SUNXI y
    kernel_conf_var USB_OHCI_HCD_PLATFORM y
    kernel_conf_var USB_PHY y
    kernel_conf_var VIDEO_SUNXI y
    kernel_conf_var VIDEO_SUNXI_CEDRUS y
    kernel_conf_var WATCHDOG y

    # boards
    kernel_conf_var LEDS_GPIO y
    kernel_conf_var MFD_AXP20X_RSB y
    kernel_conf_var MFD_AXP20X_I2C y
    kernel_conf_var NEW_LEDS y
    kernel_conf_var PWRSEQ_SIMPLE y
    kernel_conf_var REGULATOR y
    kernel_conf_var REGULATOR_FIXED_VOLTAGE y
    kernel_conf_var REGULATOR_AXP20X y

    # temp
    kernel_conf_var COMMON_CLK_SCPI y
    kernel_conf_var SENSORS_ARM_SCPI y
    kernel_conf_var COMMON_CLK_SCMI y
    kernel_conf_var SENSORS_ARM_SCMI y
    kernel_conf_var COMMON_CLK_FIXED_MMIO y
    kernel_conf_var ARM_ALLWINNER_SUN50I_CPUFREQ_NVMEM y
    kernel_conf_var CPU_FREQ y
    kernel_conf_var CPUFREQ_DT y
    kernel_conf_var ARM_SCPI_CPUFREQ y

    #kernel_conf_var PM y
    #kernel_conf_var PM_GENERIC_DOMAINS y

    # extras
    kernel_conf_var HWSPINLOCK y
    kernel_conf_var HWSPINLOCK_SUN6I y
    kernel_conf_var SPI_SPIDEV y

    # wireless
    kernel_conf_var SPARD_WLAN_SUPPORT y
    kernel_conf_var SPRDWL_NG m
    kernel_conf_var UNISOC_WIFI_PS y
    kernel_conf_var WLAN_UWE5622 m
    kernel_conf_var TTY_OVERY_SDIO m

    kernel_conf_var RFKILL m

    # bluetooth
    kernel_conf_var BT m
    kernel_conf_var BT_RFCOMM m
    kernel_conf_var BT_RFCOMM_TTY y
    kernel_conf_var BT_BNEP m
    kernel_conf_var BT_BNEP_MC_FILTER y
    kernel_conf_var BT_BNEP_PROTO_FILTER y
    kernel_conf_var BT_HIDP m
    kernel_conf_var BT_HS y
    kernel_conf_var BT_LEDS y
    kernel_conf_var BT_HCIBTUSB m
    kernel_conf_var BT_HCIBTSDIO m
    kernel_conf_var BT_HCIUART m
    kernel_conf_var BT_HCIUART_NOKIA m
    kernel_conf_var BT_HCIUART_BCSP y
    kernel_conf_var BT_HCIUART_ATH3K y
    kernel_conf_var BT_HCIUART_LL y
    kernel_conf_var BT_HCIUART_INTEL y
    kernel_conf_var BT_HCIUART_BCM y
    kernel_conf_var BT_HCIUART_RTL y
    kernel_conf_var BT_HCIUART_QCA y
    kernel_conf_var BT_HCIUART_AG6XX y
    kernel_conf_var BT_HCIUART_MRVL y
    kernel_conf_var BT_HCIBCM203X m
    kernel_conf_var BT_HCIBPA10X m
    kernel_conf_var BT_HCIBFUSB m
    kernel_conf_var BT_HCIVHCI m
}

# H6
do_configure:prepend:sun50iw6() {
    kernel_conf_var AC200_PHY y
    kernel_conf_var COMMON_CLK_PWM y
    kernel_conf_var CRYPTO y
    kernel_conf_var CRYPTO_DEV_ALLWINNER y
    kernel_conf_var CRYPTO_DEV_SUN8I_CE y
    kernel_conf_var MFD_AC200 y
    kernel_conf_var PHY_SUN50I_USB3 y
    kernel_conf_var PINCTRL_SUN50I_H6 y
    kernel_conf_var PINCTRL_SUN50I_H6_R y
    kernel_conf_var PWM_SUN4I y
    kernel_conf_var SUN50I_H6_CCU y
    kernel_conf_var SUN50I_IOMMU y
    kernel_conf_var SUN6I_MSGBOX y
    kernel_conf_var USB_DWC3 y
    kernel_conf_var VIDEO_HANTRO y

    # boards
    #kernel_conf_var ARM_ALLWINNER_SUN50I_CPUFREQ_NVMEM y
    #kernel_conf_var CPU_FREQ y
}

# H616
do_configure:prepend:sun50iw9() {
    kernel_conf_var PINCTRL_SUN50I_H616 y
    kernel_conf_var PINCTRL_SUN50I_H616_R y
    kernel_conf_var PWM_SUNXI_ENHANCE y
    kernel_conf_var SUN50I_H616_CCU y

    # boards
    kernel_conf_var MTD y
    kernel_conf_var MTD_SPI_NOR y
}

# H6 & H616
do_configure:prepend:sun50i:use-mainline-graphics() {
    kernel_conf_var DRM y
    kernel_conf_var DRM_DISPLAY_CONNECTOR y
    kernel_conf_var DRM_PANFROST y
    kernel_conf_var DRM_SUN4I y
    kernel_conf_var DRM_SUN8I_DW_HDMI y
    kernel_conf_var DRM_SUN8I_MIXER y
    kernel_conf_var DRM_SUN8I_TCON_TOP y

    kernel_conf_var SUN50I_DE2_BUS y
    kernel_conf_var SUN8I_DE2_CCU y
}

# H6
do_configure:prepend:sun50iw6:use-mainline-graphics() {
    kernel_conf_var SOUND y
    kernel_conf_var SND y
    kernel_conf_var SND_DYNAMIC_MINORS y
    kernel_conf_var SND_SOC y
    kernel_conf_var SND_SIMPLE_CARD y
    kernel_conf_var SND_SOC_ACX00 y
    kernel_conf_var SND_SUN4I_I2S y
    kernel_conf_var SND_SUN4I_SPDIF y
    kernel_conf_var SND_SUN9I_HDMI_AUDIO y
}

# H616
do_configure:prepend:sun50iw9:use-mainline-graphics() {
    kernel_conf_var SND_SOC_SUN50I_AHUB y
    kernel_conf_var SND_SOC_SUN50I_HDMI y
    kernel_conf_var SND_SUN50IW9_CODEC y
}

# Debug
do_configure:prepend() {
    #kernel_conf_var EARLY_PRINTK_DBGP y
    kernel_conf_var DYNAMIC_DEBUG y
    #kernel_conf_var CONSOLE_LOGLEVEL_DEFAULT 7
    #kernel_conf_var DEBUG_KERNEL y
    #kernel_conf_var DEBUG_DRIVER y
    #kernel_conf_var DEBUG_FS y
    #kernel_conf_var BLK_DEBUG_FS y
    kernel_conf_var PRINTK y
    #kernel_conf_var TRACING y

    # extras
    kernel_conf_var ZRAM y
    kernel_conf_var ZRAM_DEF_COMP_ZSTD y
    kernel_conf_var ZSWAP y
    kernel_conf_var ZSWAP_DEFAULT_ON y
    kernel_conf_var ZSWAP_COMPRESSOR_DEFAULT_ZSTD y

    kernel_conf_var MODULE_COMPRESS_XZ y
    
}

FILES_${KERNEL_PACKAGE_NAME}-base:append = " ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/modules.builtin.modinfo"
