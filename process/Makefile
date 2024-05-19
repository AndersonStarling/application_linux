obj-m := process.o


KERNEL_SRC = /lib/modules/$(shell uname -r)/build

build_module:
	make -C $(KERNEL_SRC) M=$(shell pwd) modules

build_app:
	gcc -o app app.c

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean




