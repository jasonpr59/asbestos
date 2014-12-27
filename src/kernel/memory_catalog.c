#include "memory_catalog.h"

void memory_catalog_initialize(struct MultibootInfo *multiboot_info) {
  cprintf("Multiboot reports %dKB of low memory and %dMB of high memory.\n",
	  multiboot_info->mem_lower, multiboot_info->mem_upper / 1024);

  size_t mmap_length = (size_t) multiboot_info->mmap_length;
  uintptr_t mmap_addr = (uintptr_t) multiboot_info->mmap_addr;
  cprintf("Looking up physical mmap at 0x%08x, with length 0x%x.\n",
	  mmap_addr, mmap_length);

  size_t offset = 0;
  while (offset < mmap_length) {
    struct MultibootMemoryMapEntry *mmap_entry =
      (struct MultibootMemoryMapEntry *) (mmap_addr + offset);
    cprintf("Size: %d\n", mmap_entry->size);
    cprintf("Addr: 0x%08x\n", mmap_entry->base_addr);
    cprintf("Length: 0x%08x\n", mmap_entry->length);
    if (mmap_entry->type == MULTIBOOT_MEMORY_USABLE) {
      cprintf("Usable.\n");
    } else {
      cprintf("Unusable.\n");
    }
    cprintf("\n");
    // Skip over the size field, and then the rest of the entry.
    offset += sizeof(mmap_entry->size) + mmap_entry->size; 
  }
}
