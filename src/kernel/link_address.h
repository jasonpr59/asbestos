#ifndef ASBESTOS_KERNEL_LINK_ADDRESS_H_
#define ASBESTOS_KERNEL_LINK_ADDRESS_H_

extern const char  kernel_start[];
extern const char kernel_end[];

// This pre-allocated chunk of memory allows us to provide a bootstrap
// allocator, even before we have a real, page-table aware allocator
// setup.
extern const char boot_heap_start[];
extern const char boot_heap_end[];

extern const char stab_entries_start[];
extern const char stab_entries_end[];

#endif  // ASBESTOS_KERNEL_LINK_ADDRESS_H_
