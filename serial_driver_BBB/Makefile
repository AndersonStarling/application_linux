obj-m := serial_driver.o

KERNEL_SRC = /home/ntai/Linux_Embedded/kernelbuildscripts/KERNEL

CROSS = /home/ntai/Linux_Embedded/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL_SRC) M=$(PWD) modules

build_app:
	/home/ntai/Linux_Embedded/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc -o app_serial_driver app_serial_driver.c

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean

copy:
	scp serial_driver.ko debian@192.168.7.2:/home/debian
	scp app_serial_driver debian@192.168.7.2:/home/debian