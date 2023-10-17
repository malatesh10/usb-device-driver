obj-m +=  1-simple-usb.o
#obj-m +=  2-simple-usb.o

KDIR = /lib/modules/$(shell uname -r)/build
make:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean

