# Default to (primary) SD
rootdev=/dev/mmcblk0p2

itest.b *0x28 == 0x00 && echo "1 U-boot loaded from SD"
itest.b *0x28 == 0x01 && echo "1 U-boot loaded from NAND"
itest.b *0x28 == 0x02 && echo "1 U-boot loaded from MMC2"
itest.b *0x28 == 0x03 && echo "1 U-boot loaded from SPI"
itest.b *0x28 == 0x10 && echo "1 U-boot loaded from MMC0 High"
itest.b *0x28 == 0x12 && echo "1 U-boot loaded from MMC2 High"

itest.b *0x10028 == 0x00 && echo "2 U-boot loaded from SD"
itest.b *0x10028 == 0x01 && echo "2 U-boot loaded from NAND"
itest.b *0x10028 == 0x02 && echo "2 U-boot loaded from MMC2"
itest.b *0x10028 == 0x03 && echo "2 U-boot loaded from SPI"
itest.b *0x10028 == 0x10 && echo "2 U-boot loaded from MMC0 High"
itest.b *0x10028 == 0x12 && echo "2 U-boot loaded from MMC2 High"

if itest.b *0x10028 == 0x02 ; then
	# U-Boot loaded from eMMC or secondary SD so use it for rootfs too
	echo "U-boot loaded from eMMC or secondary SD"
	rootdev=/dev/mmcblk1p2
fi
setenv bootargs console=${console} console=tty1 root=${rootdev} rootwait panic=10 ${extra}
# setenv bootargs console=${console} console=tty1 root=${rootdev} rootdelay=5 panic=10 ${extra}
load mmc 0:1 ${fdt_addr_r} ${fdtfile}
load mmc 0:1 ${kernel_addr_r} Image
booti ${kernel_addr_r} - ${fdt_addr_r}
