# Setup toolchain.
GCCPREFIX := "i686-elf-"
CC := $(GCCPREFIX)gcc
# Use gcc for linking, as the OSDev wiki recommends.
LD := $(GCCPREFIX)gcc
OBJDUMP := $(GCCPREFIX)objdump
AS := $(GCCPREFIX)as

# Elminate default suffix rules.
.SUFFIXES:

SRCDIR = src
LIBDIR = $(SRCDIR)/lib

# Find source files.
ASMSOURCES := $(shell find $(SRCDIR) -type f -name "*.s")
CSOURCES := $(shell find $(SRCDIR) -type f -name "*.c")
HDRFILES := $(shell find $(SRCDIR) -type f -name "*.h")

# Detect dependencies.
DEPFILES := $(patsubst %.c, %.d,$(CSOURCES))
-include $(DEPFILES)

# Setup object files.
FLAGS := -ffreestanding -O1 -gstabs
CCFLAGS := $(FLAGS) -std=c99 -Wall -Wextra -I$(LIBDIR)
CCFLAGS += -fno-omit-frame-pointer
LDFLAGS := $(FLAGS) -nostdlib -Wl,-M

OBJDIR := obj
ASMOBJS := $(patsubst $(SRCDIR)/%.s,$(OBJDIR)/%.o,$(ASMSOURCES))
COBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CSOURCES))
ALLOBJS := $(ASMOBJS) $(COBJS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CCFLAGS) -MMD -MP

$(OBJDIR)/%.o : $(SRCDIR)/%.s
	@mkdir -p $(@D)
	$(AS) -c $< -o $@


# Generate the actual kernel image.
KERNIMG := asbestos.bin
KERNASM := $(KERNIMG).asm
LDSCRIPT := linker.ld
LDMAP := asbestos.map

$(KERNIMG): $(ALLOBJS)
	@echo $(ALLOBJS)
	$(LD) -T $(LDSCRIPT) -o $@  $(LDFLAGS) $(ALLOBJS) -lgcc > $(LDMAP)
	$(OBJDUMP) -S $@ > $(KERNASM)

# Setup high-level targets.

kernel: $(KERNIMG)

clean:
	@-rm -rf $(OBJDIR) $(DEPFILES) $(KERNIMG) $(KERNASM) $(LDMAP)

QEMU := qemu-system-i386 -kernel $(KERNIMG) -serial mon:stdio -m 3G
qemu: kernel
	$(QEMU)

qemu-gdb: kernel
	$(QEMU) -gdb tcp::8998 -S
