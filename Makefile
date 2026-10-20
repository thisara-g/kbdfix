obj-m += kbdfix.o

BUILD := $(PWD)/build

all:
	mkdir -p $(BUILD)
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) MO=$(BUILD) modules

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) MO=$(BUILD) clean