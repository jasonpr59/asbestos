#include <stdint.h>
#include <x86.h>
#include "backtrace.h"
#include "cprintf.h"

static const int kNumBacktraceArgs = 3;

void print_backtrace() {
  uintptr_t *base_pointer = (uintptr_t *) get_ebp();
  // Given the value of base_pointer at the start of each iteration,
  // each iteration prints the args of the call frame at
  // *base_pointer, (i.e. one frame above base_pointer).
  while (*base_pointer != 0) {
    // What was EIP when we left the previous frame (i.e. the one that
    // this iteration is interested in)) to come to the current frame?
    uintptr_t return_pointer = *(base_pointer + 1);
    base_pointer = (uintptr_t *) *base_pointer;
    cprintf("0x%08x: ", return_pointer);
    for (int i = 0; i < kNumBacktraceArgs; i++) {
      cprintf("0x%x, ", *(base_pointer + 2 + i));
    }
    cprintf("\n");
  }

}
