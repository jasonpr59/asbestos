#ifndef ASBESTOS_KERNEL_STABS_H_
#define ASBESTOS_KERNEL_STABS_H_

#include <stdint.h>

typedef uint8_t StabType;

static const StabType kStabTypeFunction = 0x24;

struct StabEntry {
  uint32_t string_offset;
  uint8_t type;
  uint8_t other;
  uint16_t description;
  uintptr_t value;
} __attribute__((packed));

// Initialize stabs functionality.  Specifically, fill in the function
// table so that we can do function name lookups.
void stab_init();

// Get the number of stab entries.
int stab_count();

int stab_count_typed(StabType type);

// Lookup the index'th stab entry.
struct StabEntry *stab_entry(int index);

char *stab_string(struct StabEntry *entry);

#endif  // ASBESTOS_KERNEL_STABS_H_
