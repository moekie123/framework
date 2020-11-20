#/bin/bash

if [ "$HARDWARE" = "RaspberryPi" ]
then
	echo "Installing New Kernel"

#	cp $FRAMEWORK/linux/arch/arm/boot/dts/*.dtb /boot/
#	cp $FRAMEWORK/arch/arm/boot/dts/overlays/*.dtb* /boot/overlays/
#	cp $FRAMEWORK/arch/arm/boot/dts/overlays/README /boot/overlays/
#	cp $FRAMEWORK/arch/arm/boot/zImage /boot/Image.img

else
	echo "[Aborted] Script only compatible on Raspberry Pi Hardware"
fi
