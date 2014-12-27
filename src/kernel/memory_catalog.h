#ifndef ASBESTOS_KERNEL_MEMORY_CATALOG_H_
#define ASBESTOS_KERNEL_MEMORY_CATALOG_H_

#include <stddef.h>
#include "multiboot.h"

static const size_t kMemoryCatalogBlockSize = 1 << 12;

struct MemoryCatalogBlock {
  uintptr_t address;
  struct MemoryCatalogBlock *next;
};

void memory_catalog_initialize(struct MultibootInfo *multiboot_info);

#endif  // ASBESTOS_KERNEL_MEMORY_CATALOG_H_
