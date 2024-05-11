PWD := $(shell pwd)
KERNEL_SRC = /home/ntai/Linux_Embedded/kernelbuildscripts/KERNEL

CROSS = /home/ntai/Linux_Embedded/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

obj-m += lcd_i2c.o

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL_SRC) M=$(PWD) modules
	/home/ntai/Linux_Embedded/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc -o app app.c
clean:
	make -C $(KERNEL) M=$(PWD) clean

copy:
	scp lcd_i2c.ko debian@192.168.7.2:/home/debian
	scp app debian@192.168.7.2:/home/debian
