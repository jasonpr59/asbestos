#ifndef ASBESTOS_KERNEL_PAGE_H_
#define ASBESTOS_KERNEL_PAGE_H_

#include <stdbool.h>
#include <stdint.h>

// Useful references:
// INTEL 80386 PROGRAMMER'S REFERENCE MANUAL 1986 Section 5.2

#define ALL_PAGE_TABLES_SIZE (1 << 22)

// See Programmer's Reference Manual, Figure 5-10.
struct PageTableEntry{
  bool present : 1;
  bool writable : 1;
  bool user_level : 1;
  unsigned int zeroes_1 : 2;
  bool accessed : 1;
  bool dirty : 1;
  unsigned int zeroes_2 : 2;
  // Available for system programmers' use.
  unsigned int avail_1 : 3;
  unsigned int page_frame_addr : 20;
} __attribute__((packed));

void setup_paging();

#endif  // ASBESTOS_KERNEL_PAGE_H_
