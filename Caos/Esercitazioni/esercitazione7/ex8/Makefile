PWD := $(CURDIR)

obj-m += ex8.o
ex8-objs := init.o exit.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
