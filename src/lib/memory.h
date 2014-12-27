#ifndef ASBESTOS_LIB_MEMORY_H_
#define ASBESTOS_LIB_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

static const size_t kPageSize = 1 << 12;
static const int kPagesPerMemorySpace = 1 << 20;

uintptr_t aligned_up(uintptr_t address, size_t block_size);

#endif  // ASBESTOS_LIB_MEMORY_H_
