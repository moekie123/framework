#/bin/bash
echo "Start Build Script"

KERNEL=kernel7

make modules_install

echo "Copy Kernel to /boot-partition"
cp arch/arm/boot/dts/*.dtb /boot/
cp arch/arm/boot/dts/overlays/*.dtb* /boot/overlays/
cp arch/arm/boot/dts/overlays/README /boot/overlays/
cp arch/arm/boot/zImage /boot/$KERNEL.img

echo "Finished Build Script"
