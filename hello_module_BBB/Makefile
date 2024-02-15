obj-m := hello_module_BBB.o

KERNEL_SRC = /home/ntai/Linux_Embedded/kernelbuildscripts/KERNEL

CROSS = /home/ntai/Linux_Embedded/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean

copy:
	scp hello_module_BBB.ko debian@192.168.7.2:/home/debian

