obj-m := device_file_kernel_module.o


KERNEL_SRC = /lib/modules/$(shell uname -r)/build

build_module:
	make -C $(KERNEL_SRC) M=$(shell pwd) modules

build_app:
	gcc -o app_device_file app_device_file.c

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean
	rm ./app_device_file







