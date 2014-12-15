/* This file is basically copied from http://wiki.osdev.org/Bare_Bones. */

ENTRY(_start)

SECTIONS
{
	/* Start loading sections at 1MiB. This is conventional. */
	. = 1M;

	/* Put multiboot header first, to ensure the bootloader
	   recognizes it. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized). */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack. */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
}
