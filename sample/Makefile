KSRC = /home/kenji/work/rasp/linux
ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-
#EXTRA_CFLAGS += -DCONFIG_LITTLE_ENDIAN

obj-m := hello.o

all:
	make -C $(KSRC) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KSRC) M=$(PWD) clean
