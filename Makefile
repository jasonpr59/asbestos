# Setup toolchain.
GCCPREFIX := "i686-elf-"
CC := $(GCCPREFIX)gcc
AS := $(GCCPREFIX)as

FLAGS := -ffreestanding -O1 -g
CCFLAGS := $(FLAGS) -std=c99 -Wall -Wextra
LDFLAGS := $(FLAGS) -nostdlib


# Elminate default suffix rules.
.SUFFIXES:


# Find source files.
ASMSOURCES := $(shell find kernel -type f -name "*.s")
CSOURCES := $(shell find kernel -type f -name "*.c")
HDRFILES := $(shell find kernel -type f -name "*.h")


# Setup object files.
OBJDIR := obj
ASMOBJS := $(patsubst %.s,$(OBJDIR)/%.o,$(ASMSOURCES))
COBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(CSOURCES))
ALLOBJS := $(ASMOBJS) $(COBJS)

$(OBJDIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CCFLAGS)

$(OBJDIR)/%.o : %.s
	@mkdir -p $(@D)
	$(AS) -c $< -o $@


# Generate the actual kernel image.
KERNIMG := asbestos.bin
LDSCRIPT := linker.ld

$(KERNIMG): $(ALLOBJS)
	@echo $(ALLOBJS)
	$(CC) -T $(LDSCRIPT) -o $@  $(LDFLAGS) $(ALLOBJS) -lgcc


# Setup high-level targets.

kernel: $(KERNIMG)

clean:
	@-rm -rf $(OBJDIR) $(KERNIMG)

