#include <memory.h>

#include "boot_allocator.h"
#include "link_address.h"
#include "panic.h"

// boot_heap_start is page-aligned.
static uintptr_t remaining_boot_heap = (uintptr_t) boot_heap_start;

uintptr_t boot_allocate(size_t length) {
  size_t page_aligned_length = aligned_up(length, kPageSize);
  uintptr_t allocation = remaining_boot_heap;
  remaining_boot_heap += page_aligned_length;
  if (remaining_boot_heap > (uintptr_t) boot_heap_end) {
    panic("Boot allocator out of memory.\n");
  }
  return allocation;
}

