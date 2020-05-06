obj-m += pwm-pca9685.o

KDIR=/usr/src/linux/
LDIR=/lib/modules/$(shell uname -r)/kernel/drivers/pwm/

all:
	make -C ${KDIR} M=$(PWD) modules

install:
	make -C ${KDIR} M=$(PWD) modules
	
	modprobe -r pwm-pca9685

	cp --interactive --force $(PWD)/pwm-pca9685.ko ${LDIR}

	modprobe pwm-pca9685



clean:
	@echo "clean modules"
