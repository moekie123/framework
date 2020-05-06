obj-m += pwm-pca9685.o

KDIR=/usr/src/linux/
LDIR=/lib/modules/$(shell uname -r)/kernel/drivers/pwm/

all:
	@echo "Build Kernel Modules"
	make -C ${KDIR}  M=$(PWD) modules

install:
	@echo "Install Kernel Modules"

	make -C ${KDIR} M=$(PWD) modules
	
	modprobe -r pwm-pca9685

	cp --interactive --force $(PWD)/pwm-pca9685.ko ${LDIR}

	modprobe pwm-pca9685
