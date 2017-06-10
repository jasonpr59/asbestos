#include <x86.h>
#include <memory.h>

#include "cprintf.h"
#include "link_address.h"
#include "memory_catalog.h"
#include "page.h"
#include "panic.h"

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

void zero_out_page(uintptr_t start);
physptr allocate_page_table();
void map(physptr dir, virtptr virtual, physptr physical);

const struct PageTableEntry kZeroEntry = {};

void setup_paging() {
  // Permanently allocate a page for kernel_page_dir.
  physptr kernel_page_dir = (physptr) memory_catalog_allocate_page()->address;
  // Set the "present" bits (and all other bits) to zero.
  zero_out_page((uintptr_t) kernel_page_dir);

  for (physptr page_loc = (physptr) kernel_start;
       page_loc < (physptr) kernel_end;
       page_loc += kPageSize) {
    map(kernel_page_dir, (virtptr) page_loc, page_loc);
  }

  // Previously, the end of the kernel had a physical address.  But,
  // now that we've identity-mapped all in-use kernel memory, we can
  // start treating it like a virtual address.
  virtptr mem_top = (virtptr) kernel_end;

  // Set aside virtual memory for the recursive page table.
  virtptr rpt = aligned_up(mem_top, ALL_PAGE_TABLES_SIZE);
  mem_top += ALL_PAGE_TABLES_SIZE;

  // Let (31:22=rpt,21:12=rpt,11:0=000) point to the first entry in the page table.
  // ie. let the (physical) address pointed to by the rpt'th entry be
  // the physical address of the page table itself.
  struct PageTableEntry *rpt_self = (
      (struct PageTableEntry *) kernel_page_dir) + (rpt >> DIR_SHIFT);
  rpt_self->page_frame_addr = kernel_page_dir >> TABLE_SHIFT;
  rpt_self->writable = true;
  rpt_self->present = true;

  // Identity-map the VGA memory space.
  // TODO(jasonpr): Re-use definitions from vga.h to justify the address,
  // and to justify that only one page needs mapping.
  map(kernel_page_dir, (virtptr) 0xB8000, (physptr) 0xB8000);

  set_cr3(kernel_page_dir);
  set_cr0(get_cr0() | (1 << CR0_PAGING_BIT));
}

// map virtual to physical, in a page tree rooted at dir.  Do not call
// after paging is enabled (hence dir is a physptr).
void map(physptr dir, virtptr virtual, physptr physical) {
  struct PageTableEntry *dir_entry = (struct PageTableEntry *) dir;
  uint16_t dir_num = (DIR_MASK & virtual) >> DIR_SHIFT;
  dir_entry += dir_num;
  if (!dir_entry->present) {
    physptr page_addr = allocate_page_table();
     *dir_entry = kZeroEntry;
    dir_entry->page_frame_addr = ((unsigned int) page_addr) >> TABLE_SHIFT;
    dir_entry->writable = true;
    dir_entry->present = true;
  }

  struct PageTableEntry *tbl_entry = (
      (struct PageTableEntry *) (dir_entry->page_frame_addr << TABLE_SHIFT));
  uint16_t page_num = (TABLE_MASK & virtual) >> TABLE_SHIFT;
  tbl_entry += page_num;
  if (tbl_entry->present) {
    panic("Table entry already present.  Dir %d, table %d", dir_num, page_num);
    return;
  }
  *tbl_entry = kZeroEntry;
  tbl_entry->page_frame_addr = ((unsigned int) physical) >> TABLE_SHIFT;
  tbl_entry->present = true;
  tbl_entry->writable = true;
}


physptr allocate_page_table() {
  // TODO(jasonpr): Maybe pre-define which physical pages get allocated
  // in linker.ld.  Just because we *can* use any old page for the
  // kernel page tables doesn't mean we should.  And we've already
  // reserved a 4M block of virtual addresses for the kernel page tables...
  // why not make them equal to the physical ones?

  // Right now, this allocation is permanent. We can only allocate up
  // to 4MB of page tables, and its unlikely that many tables will
  // become unused, so this is fine.
  uintptr_t page_table = memory_catalog_allocate_page()->address;
  zero_out_page(page_table);
  return (physptr) page_table;
}

void zero_out_page(uintptr_t start) {
  for (char *i = (char *) start; i < (char *) start + kPageSize; i++) {
    *i = 0;
  }
}
