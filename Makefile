obj-m += kbdfix.o

KVER     := $(shell uname -r)
KDIR     := /lib/modules/$(KVER)/build
BUILD    := $(PWD)/build
MOK_KEY  := /var/lib/shim-signed/mok/MOK.priv
MOK_CERT := /var/lib/shim-signed/mok/MOK.der

all:
	mkdir -p $(BUILD)
	$(MAKE) -C $(KDIR) M=$(PWD) MO=$(BUILD) modules

sign: all
	sudo /usr/src/linux-headers-$(KVER)/scripts/sign-file sha256 \
		$(MOK_KEY) $(MOK_CERT) $(BUILD)/kbdfix.ko

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) MO=$(BUILD) clean

.PHONY: all sign clean