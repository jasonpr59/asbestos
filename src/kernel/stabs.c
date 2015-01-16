#include "link_address.h"
#include "panic.h"
#include "cprintf.h"
#include "stabs.h"


struct StabEntry *stab_entries = (struct StabEntry *) stab_entries_start;

struct StabEntry *stab_entry(int index) {
  int stab_size = ((stab_entries_end - stab_entries_start)
		   / sizeof(struct StabEntry));
  if (index >= stab_size) {
    panic("STAB index out of bounds.\n");
  }

  return &stab_entries[index];
}
