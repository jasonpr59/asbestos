#include "memory.h"

// Rounds an address up to a block boundary.
// Requires that the block size is a power of two.
uintptr_t aligned_up(uintptr_t address, size_t block_size) {
  return (address + block_size - 1) & ~(block_size - 1);
}
