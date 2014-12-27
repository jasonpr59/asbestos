#ifndef ASBESTOS_KERNEL_LINK_ADDRESS_H_
#define ASBESTOS_KERNEL_LINK_ADDRESS_H_

extern const char  kernel_start[];
extern const char kernel_end[];

// This pre-allocated chunk of memory holds data for tracking the rest
// of the system's available memory.
extern const char mem_catalog_start[];
extern const char mem_catalog_end[];

#endif  // ASBESTOS_KERNEL_LINK_ADDRESS_H_
