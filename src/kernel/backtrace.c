#include <stdint.h>
#include <x86.h>
#include "backtrace.h"
#include "cprintf.h"

static const int kNumBacktraceArgs = 3;

void print_backtrace() {
  uintptr_t *base_pointer = (uintptr_t *) get_ebp();
  while (base_pointer != 0) {
    uintptr_t return_pointer = *(base_pointer + 1);
    base_pointer = (uintptr_t *) *base_pointer;
    cprintf("0x%08x: ", return_pointer);
    for (int i = 0; i < kNumBacktraceArgs; i++) {
      cprintf("0x%x, ", *(base_pointer + 2 + i));
    }
    cprintf("\n");
  }

}
