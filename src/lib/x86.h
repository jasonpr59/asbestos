#ifndef X86_H_
#define X86_H_

#include <stdint.h>

// This file is heavily influenced by JOS's inc/x86.h.

// Usually, we discourage inlining via command line flags. But, we
// want our instruction wrapper functions to be inlined.  So, we mark
// all of them with always_inline.

static __inline void outb(int io_port, uint8_t data) __attribute__((always_inline));

// The OUTB instruction constrains which registers we use.
// See http://x86.renejeschke.de/html/file_module_x86_id_222.html.
static void outb(int io_port, uint8_t data) {
  __asm __volatile("outb %0, %w1" :
		   /* No output. */ : 
		   "a" (data), "d" (io_port));
}
#endif  // X86_H_
