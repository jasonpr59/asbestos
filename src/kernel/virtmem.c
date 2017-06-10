#include <memory.h>
#include "memory_catalog.h"
#include "cprintf.h"
#include "page.h"
#include "panic.h"
#include "virtmem.h"

// Within this file, it's useful to be explicit whether an address is
// physical or virtual.
typedef uintptr_t physptr;
typedef uintptr_t virtptr;

// Gets the bits of a virtual address that identify the page
// directory.
#define DIR_SHIFT 22
#define DIR_MASK (0x3FF << DIR_SHIFT)
// Gets the bits of a virtual address that identify the page table,
// underneath the page directory.
#define TABLE_SHIFT 12
#define TABLE_MASK (0x3FF << TABLE_SHIFT)
#define CR0_PAGING_BIT 31

const struct PageTableEntry kAllocatorZeroEntry = {};

static virtptr mem_top;
static virtptr rpt;
static virtptr rpd;

struct PageTableEntry * get_dir_entry(virtptr page) {
  return ((struct PageTableEntry *) rpd) + (page >> DIR_SHIFT);
}

struct PageTableEntry * get_table_entry(virtptr page) {
  return ((struct PageTableEntry *) rpt) + (page >> TABLE_SHIFT);
}

void allocate_page(virtptr new_page) {
  struct PageTableEntry *dir_entry = get_dir_entry(new_page);

  if (!dir_entry->present) {
    // TODO(jasonpr): Update memory_catalog to make it easy to free pages,
    // then allow page tables to be freed.
    physptr table = memory_catalog_allocate_page()->address;
    *dir_entry = kAllocatorZeroEntry;
    dir_entry->page_frame_addr = table >> TABLE_SHIFT;
    dir_entry->present = true;
  }

  struct PageTableEntry *table_entry = get_table_entry(new_page);
  if (table_entry->present) {
    panic("Page table entry already present for: 0x%08x", new_page);
  }

  // Sure, everything is a page.  This is the page that we originally set out to allocate,
  // backing the virtptr 'new_page'.
  // TODO(jasonpr): Upate memory_catalog to make it easy to free pages,
  // then provide a mechanism to free virtual memory and free the physical pages.
  physptr page = memory_catalog_allocate_page()->address;
  *table_entry = kAllocatorZeroEntry;
  table_entry->page_frame_addr = page >> TABLE_SHIFT;
  table_entry->present = true;
}

void virtmem_setup_allocator(uintptr_t rpt_in) {
  rpt = rpt_in;
  rpd = (virtptr) (rpt | (rpt >> (DIR_SHIFT - TABLE_SHIFT)));

  struct PageTableEntry *dir_entry = (struct PageTableEntry *) rpd;
  int highest_dir_num = 0;
  for (int i = 0; i < 1024; i++) {
    if (dir_entry->present) {
      highest_dir_num = i;
    }
    dir_entry++;
  }

  virtptr highest_dir_for = rpt + (highest_dir_num << TABLE_SHIFT);
  mem_top = rpt + ALL_PAGE_TABLES_SIZE;

  // mem_top is is guaranteed not to be mapped yet (otherwise another
  // dir would have ben present).  Still, let's do a sanity check
  // before returning.
  if (highest_dir_for != rpd) {
    // The recursive page table was the last block of memory allocated
    // during paging setup.  So, its address must be the address
    // handled by the highest page dir.
    panic("Recursive page dir is at 0x%08x, but highest dir handles 0x%08x\n",
	  rpd, highest_dir_for);
  }


  cprintf("First unused byte in kernel memory space: 0x%08x\n", mem_top);
}

uintptr_t virtmem_allocate(size_t bytes) {
  if (bytes % kPageSize != 0) {
    // TODO(jasonpr): Maybe just return NULL?
    panic("Tried to allocate %d bytes (non-multiple of %d)", bytes, kPageSize);
  }
  virtptr base = mem_top;
  mem_top += bytes;
  for (virtptr new_page = base; new_page < mem_top; new_page += kPageSize) {
    allocate_page(new_page);
  }
  return (uintptr_t) base;
}





  
