#ifndef ASBESTOS_KERNEL_STABS_H_
#define ASBESTOS_KERNEL_STABS_H_

#include <stdint.h>

struct StabEntry {
  uint32_t string_offset;
  uint8_t type;
  uint8_t other;
  uint16_t description;
  uintptr_t value;
} __attribute__((packed));

// Lookup the index'th stab entry.
struct StabEntry *stab_entry(int index);

#endif  // ASBESTOS_KERNEL_STABS_H_
