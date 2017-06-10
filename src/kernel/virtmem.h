#ifndef ASBESTOS_KERNEL_VIRTMEM_H_
#define ASBESTOS_KERNEL_VIRTMEM_H_

#include <stddef.h>
#include <stdint.h>

// Prepare to handle allocate() calls.  Use the recursive page table
// mapping at *rpt to decide the highest allocated address, and start
// allocating virtual addresses on top of that.
void virtmem_setup_allocator(uintptr_t rpt);

// Allocate a contiguous block of virtual memory.  Return a pointer to
// the first byte.  This block cannot be freed.
uintptr_t virtmem_allocate(size_t bytes);

#endif  // ASBESTOS_KERNEL_VIRTMEM_H_
