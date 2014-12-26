#ifndef X86_H_
#define X86_H_

#include <stdint.h>

// This file is heavily influenced by JOS's inc/x86.h.

// Usually, we discourage inlining via command line flags. But, we
// want our instruction wrapper functions to be inlined.  So, we mark
// all of them with always_inline.

static __inline uintptr_t get_ebp() __attribute__((always_inline));
static __inline uint8_t inb(uint16_t io_port) __attribute__((always_inline));
static __inline void outb(uint16_t io_port, uint8_t data) __attribute__((always_inline));

// Get the current base pointer.

// This wil be the base pointer of the calling function, because
// get_ebp() is always inlined.
static uintptr_t get_ebp() {
  uintptr_t ebp;
  __asm __volatile("mov %%ebp, %0" :
		   "=r" (ebp));
  return ebp;
}

static uint8_t inb(uint16_t io_port) {
  uint8_t data;
  __asm __volatile("inb %1, %0" :
		   "=a" (data) :
		   "d" (io_port));
  return data;
}

// The OUTB instruction constrains which registers we use.
// See http://x86.renejeschke.de/html/file_module_x86_id_222.html.
static void outb(uint16_t io_port, uint8_t data) {
  __asm __volatile("outb %0, %1" :
		   /* No output. */ : 
		   "a" (data), "d" (io_port));
}

struct PushedRegisters {
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
};

#endif  // X86_H_
