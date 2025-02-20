USER_APP = user_app
obj-m += ex1.o 
ex1-objs := chdev.o

PWD := $(CURDIR) 
 
all: 
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	$(CC) -o $(USER_APP) $(USER_APP).c
 
clean: 
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm $(USER_APP)
