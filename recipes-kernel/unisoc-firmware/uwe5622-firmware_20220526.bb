DESCRIPTION = "Unisoc uwe5622 WiFi/Bluetooth firmware"
LICENSE = "CC0-1.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/${LICENSE};md5=0ceb3372c9595f0a8067e55da801e4a1"

#PV = "1.0"
#PR = "r0"

COMPATIBLE_MACHINE = "(orange-pi-zero2|orange-pi-3-lts)"

SRC_URI = "git://github.com/orangepi-xunlong/firmware.git;protocol=https;nobranch=1"
SRCREV = "3761ac64a56e69fe371a86262203ed69465747fc"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${base_libdir}/firmware
    for file in wcnmodem.bin wifi_2355b001_1ant.ini bt_configure_rf.ini bt_configure_pskey.ini; do
        install -m 0644 ${S}/$file ${D}${base_libdir}/firmware/
    done
}

FILES:${PN} = "${base_libdir}/*"

PACKAGES = "${PN}"
