#include "cprintf.h"
#include "link_address.h"
#include "memory_catalog.h"
#include "panic.h"

// The free list initially includes a block for every usable bit of memory,
// except for memory that the linker already allocated for the kernel.
// Then, it is updated as clients allocated and free memory.
static struct MemoryCatalogBlock *free_list = NULL;

// Only used during initialization.
static struct MemoryCatalogBlock *next_unused_block =
    (struct MemoryCatalogBlock *) mem_catalog_start;

void catalog_memory_block(uintptr_t address) {
  if (address >= (uintptr_t) kernel_start
      && address < (uintptr_t) kernel_end) {
    // We're (possibly) already using this page.  Do not add it
    // allocation system.
    return;
  }
  struct MemoryCatalogBlock *block = next_unused_block++;
  block->address = address;
  // Push it onto the free list.
  block->next = free_list;
  free_list = block;
}

// Rounds an address up to a block boundary.
// Requires that the block size is a power of two.
uintptr_t aligned_up(uintptr_t address, size_t block_size) {
  return (address + block_size - 1) & ~(block_size - 1);
}

// Adds a range of memory to the free list.
// Requries that base_address is kMemoryCatalogBlockSize aligned.
void catalog_memory_range(uintptr_t base_address, size_t length) {
  cprintf("Adding range [0x%08x, ...) to free list.\n", base_address);
  for (size_t offset = 0; offset < length; offset += kMemoryCatalogBlockSize) {
    catalog_memory_block(base_address + offset);
  }
}

struct MemoryCatalogBlock *memory_catalog_allocate_page() {
  if (!free_list) {
    panic("Ran out of pages.\n");
  }
  struct MemoryCatalogBlock *block = free_list;
  free_list = block->next;
  return block;
}

void memory_catalog_free_page(struct MemoryCatalogBlock *block) {
  block->next = free_list;
  free_list = block;
}

void memory_catalog_initialize(struct MultibootInfo *multiboot_info) {
  int memory_size_kibibytes = (multiboot_info->mem_lower +
			       multiboot_info->mem_upper);
  cprintf("Found %dMB of usable RAM.\n", memory_size_kibibytes / 1024);

  size_t mmap_length = (size_t) multiboot_info->mmap_length;
  uintptr_t mmap_addr = (uintptr_t) multiboot_info->mmap_addr;

  size_t offset = 0;
  while (offset < mmap_length) {
    struct MultibootMemoryMapEntry *mmap_entry =
      (struct MultibootMemoryMapEntry *) (mmap_addr + offset);
    if (mmap_entry->type == MULTIBOOT_MEMORY_USABLE) {
      uintptr_t base_addr = mmap_entry->base_addr;
      if (base_addr % kMemoryCatalogBlockSize) {
	// TODO(jasonpr): Don't panic. Just round up, lessen the
	// length accordingly, and carry on.
	panic("Got misaligned memory mapping from bootloader: 0x%0x.\n",
	      base_addr);
      }
      catalog_memory_range(base_addr, mmap_entry->length);
    }
    // Skip over the size field, and then the rest of the entry.
    offset += sizeof(mmap_entry->size) + mmap_entry->size; 
  }
}
