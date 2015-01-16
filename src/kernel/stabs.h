#ifndef ASBESTOS_KERNEL_STABS_H_
#define ASBESTOS_KERNEL_STABS_H_

#include <stdint.h>

#define STAB_TYPE_FUNCTION 0x24

struct StabEntry {
  uint32_t string_offset;
  uint8_t type;
  uint8_t other;
  uint16_t description;
  uintptr_t value;
} __attribute__((packed));

// Lookup the index'th stab entry.
struct StabEntry *stab_entry(int index);

char *stab_string(struct StabEntry *entry);

#endif  // ASBESTOS_KERNEL_STABS_H_
