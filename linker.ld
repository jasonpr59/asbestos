/* This file is basically copied from http://wiki.osdev.org/Bare_Bones. */

ENTRY(_start)

SECTIONS
{
	/* Start loading sections at 1MiB. This is conventional. */
	. = 1M;
	PROVIDE(kernel_start = .);

	/* Put multiboot header first, to ensure the bootloader
	   recognizes it. */
	.text BLOCK(4K) :
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) :
	{
		*(.rodata)
	}

	/* Read-write data (initialized). */
	.data BLOCK(4K) :
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack. */
	.bss BLOCK(4K) :
	{
		*(.COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	/* STAB entries. */
	.stab BLOCK(4K) :
	{
		stab_entries_start = .;
		*(.stab)
		stab_entries_end = .;

		/* Force the linker to load/allocate this section.  By
		default, normal ELF loaders, including bootloaders,
		decline to load this data into memory, and leave the
		data to be loaded only by the debugger.  But, we want
		to load the STAB data, so the kernel produce nice
		backtraces of itself. */
		BYTE(0);
	}

	/* STAB strings. */
	.stabstr BLOCK(4K) :
	{
		stab_strings_start = .;
		*(.stabstr)
		stab_strings_end = .;

		/* As with the .stab section, force the linker to
		load/allocate this section. */
		BYTE(0);
	}

	. = ALIGN(4K);
	/* The boot heap is a contiguous region of memory from which
	we allocate memory until we set up our real, page-table aware
	allocator. */
	PROVIDE(boot_heap_start = .);
	. += 8M;
	PROVIDE(boot_heap_end = .);

	PROVIDE(kernel_end = .);
}
