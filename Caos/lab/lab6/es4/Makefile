PWD := $(CURDIR)

obj-m += ex4.o
ex4-objs := init.o string_rev.o exit.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
