DESCRIPTION = "Linux Kernel"

INC_PR = "r0"

inherit kernel kernel-yocto siteinfo

# Enable OABI compat for people stuck with obsolete userspace
ARM_KEEP_OABI ?= "0"

# Set the verbosity of kernel messages during runtime
# You can define CMDLINE_DEBUG in your local.conf or distro.conf to override this behaviour
CMDLINE_DEBUG ?= "loglevel=3"

# Kernel bootlogo is distro-specific (default is OE logo).
# Logo resolution (qvga, vga, ...) is machine-specific.
LOGO_SIZE ?= '${@oe.utils.conditional("MACHINE_GUI_CLASS", "bigscreen", "vga", "qvga", d)}'
# To use this, add file://${LOGO_SIZE}/logo_linux_clut224.ppm.bz2 or similar
# to your kernel recipe, and then structure your logos for each resolution
# accordingly.

LOCALVERSION ?= ""
KCONFIG_MODE ?= "alldefconfig"
KMACHINE ?= "${MACHINE}"

#kernel_conf_var CMDLINE "\"${CMDLINE} ${CMDLINE_DEBUG}\""
kernel_conf_var() {
    CONF_SED_SCRIPT="$CONF_SED_SCRIPT /CONFIG_$1[ =]/d;"
    if test "$2" = "n"
    then
        echo "# CONFIG_$1 is not set" >> ${B}/.config
    else
        echo "CONFIG_$1=$2" >> ${B}/.config
    fi
}

do_kernel_configme[depends] += "virtual/${TARGET_PREFIX}binutils:do_populate_sysroot"
do_kernel_configme[depends] += "virtual/${TARGET_PREFIX}gcc:do_populate_sysroot"
do_kernel_configme[depends] += "bc-native:do_populate_sysroot bison-native:do_populate_sysroot"

do_configure:prepend() {
    CONF_SED_SCRIPT=""

    #
    # logo support, if you supply logo_linux_clut224.ppm in SRC_URI, then it's going to be used
    #
    if [ -e ${WORKDIR}/logo_linux_clut224.ppm ]; then
        install -m 0644 ${WORKDIR}/logo_linux_clut224.ppm drivers/video/logo/logo_linux_clut224.ppm
        kernel_conf_var LOGO y
        kernel_conf_var LOGO_LINUX_CLUT224 y
    fi

    #
    # oabi / eabi support
    #
    kernel_conf_var AEABI y
    if [ "${ARM_KEEP_OABI}" = "1" ] ; then
        kernel_conf_var OABI_COMPAT y
    else
        kernel_conf_var OABI_COMPAT n
    fi

    # When enabling thumb for userspace we also need thumb support in the kernel
    if [ "${ARM_INSTRUCTION_SET}" = "thumb" ] ; then
        kernel_conf_var ARM_THUMB y
    fi

    kernel_conf_var CMDLINE "\"${CMDLINE} ${CMDLINE_DEBUG}\""

    kernel_conf_var LOCALVERSION "\"${LOCALVERSION}\""
    kernel_conf_var LOCALVERSION_AUTO n

    kernel_conf_var SYSFS_DEPRECATED n
    kernel_conf_var SYSFS_DEPRECATED_V2 n
    kernel_conf_var HOTPLUG y
    kernel_conf_var UEVENT_HELPER_PATH \"\"
    kernel_conf_var UNIX y
    kernel_conf_var SYSFS y
    kernel_conf_var PROC_FS y
    kernel_conf_var TMPFS y
    kernel_conf_var INOTIFY_USER y
    kernel_conf_var SIGNALFD y
    kernel_conf_var TMPFS_POSIX_ACL y
    kernel_conf_var BLK_DEV_BSG y
    kernel_conf_var DEVTMPFS y
    kernel_conf_var DEVTMPFS_MOUNT y

    # Newer inits like systemd need cgroup support
    if [ "${KERNEL_ENABLE_CGROUPS}" = "1" ] ; then
        kernel_conf_var CGROUP_SCHED y
        kernel_conf_var CGROUPS y
        kernel_conf_var CGROUP_NS y
        kernel_conf_var CGROUP_FREEZER y
        kernel_conf_var CGROUP_DEVICE y
        kernel_conf_var CPUSETS y
        kernel_conf_var PROC_PID_CPUSET y
        kernel_conf_var CGROUP_CPUACCT y
        kernel_conf_var RESOURCE_COUNTERS y
    fi

    #
    # root-over-nfs-over-usb-eth support. Limited, but should cover some cases.
    # Enable this by setting a proper CMDLINE_NFSROOT_USB.
    #
    if [ ! -z "${CMDLINE_NFSROOT_USB}" ]; then
        bbnote "Configuring the kernel for root-over-nfs-over-usb-eth with CMDLINE ${CMDLINE_NFSROOT_USB}"
        kernel_conf_var INET y
        kernel_conf_var IP_PNP y
        kernel_conf_var USB_GADGET y
        kernel_conf_var USB_GADGET_SELECTED y
        kernel_conf_var USB_ETH y
        kernel_conf_var NFS_FS y
        kernel_conf_var ROOT_NFS y
        kernel_conf_var CMDLINE \"${CMDLINE_NFSROOT_USB} ${CMDLINE_DEBUG}\"
    fi

    yes '' | oe_runmake -C ${S} O=${B} oldconfig
}

do_configure:append() {
    if test -e scripts/Makefile.fwinst ; then
        sed -i -e "s:-m0644:-m 0644:g" scripts/Makefile.fwinst
    fi
}
