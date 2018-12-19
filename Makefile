CSOURCES := $(shell find $(SOURCEDIR) -name '*.c')
SSOURCES := $(shell find $(SOURCEDIR) -name '*.s')
CPPSOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')

ARMGNU ?= arm-none-eabi

GCCARGS = -mcpu=cortex-a53 -mfloat-abi=softfp -mfpu=neon-fp-armv8 -nostartfiles


all: kernel.img clear_extra


kernel.elf:
	$(ARMGNU)-gcc $(GCCARGS) -g $(SSOURCES) $(CSOURCES) $(CPPSOURCES) -T memmap -o kernel.elf

kernel.img: kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

clear: clear_extra
	rm -f *.img

clear_extra:
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	