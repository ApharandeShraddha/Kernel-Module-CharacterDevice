obj-m := kernelProcessList.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm userProcessList

usercode:userProcessList.c
	gcc -o userProcessList userProcessList.c

insert:
	sudo insmod ./kernelProcessList.ko

remove:
	sudo rmmod kernelProcessList

access:
	sudo chmod 777 /dev/process_list

run:
	./userProcessList
