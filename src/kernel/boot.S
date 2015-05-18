# This file is heavily influenced by http://wiki.osdev.org/Bare_Bones.
# (Dummy change to overcome git case sensitivity bug.)

# Declare constants used for creating a multiboot header.
# Align loaded modules on page boundaries.
.set ALIGN, 1<<0
# Provide memory map.
.set MEMINFO, 1<<1
# Make the multiboot 'flag' field.
.set FLAGS, ALIGN | MEMINFO
# This magic number lets the bootloader find the header.
.set MAGIC, 0x1BADB002
# Make a checksum of the above, to prove we are multiboot.
.set CHECKSUM, -(MAGIC + FLAGS)

# Write the multiboot header.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Setup our own stack.
# TODO(jasonpr): Investigate arguments at
# http://sourceware.org/binutils/docs/as/Section.html.
.section .bootstrap_stack, "aw", @nobits
stack_end:
.skip 16384
stack_start:

# The entry point.  The linker script will cause us to enter here.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_start, %esp
	# The C-code entry point will be kernel_main()
	pushal
	// Indicate that this is the base stack frame.
	mov $0, %ebp
	call kernel_main
	# If we mistakenly return, just loop endlessly.
	cli
.hang_loop:
	jmp .hang_loop

# Set the size of the _start symbol.  This is apparently useful for debugging
# and call tracing.
.size _start, . - _start
