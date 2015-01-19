#include "link_address.h"
#include "panic.h"
#include "cprintf.h"
#include "stabs.h"

static const char *kEmptyString = "";

struct StabEntry *stab_entries = (struct StabEntry *) stab_entries_start;

void stab_init() {

}

int stab_count() {
  return (stab_entries_end - stab_entries_start) / sizeof(struct StabEntry);
}

int stab_count_typed(StabType type) {
  int count_builder = 0;
  for (int i = 0; i < stab_count(); i++) {
    count_builder += (stab_entry(i)->type == type);
  }
  return count_builder;
}

struct StabEntry *stab_entry(int index) {
  if (index >= stab_count()) {
    panic("STAB index out of bounds.\n");
  }

  return &stab_entries[index];
}

char *stab_string(struct StabEntry *entry) {
  uint32_t offset = entry->string_offset;
  if (offset == 0) {
    // TODO(jasonpr): Determine how to do this without endangering our
    // kEmptyString by allowing the client to mess with it.
    return (char *) kEmptyString;
  }
  return (char *) stab_strings_start + offset;
}
