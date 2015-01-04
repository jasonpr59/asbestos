#ifndef ASBESTOS_KERNEL_BOOT_ALLOCATOR_H_
#define ASBESTOS_KERNEL_BOOT_ALLOCATOR_H_

#include <stddef.h>
#include <stdint.h>

uintptr_t boot_allocate(size_t length);

#endif  // ASBESTOS_KERNEL_BOOT_ALLOCATOR_H_
