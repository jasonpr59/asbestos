#ifndef X86_H_
#define X86_H_

#include <stdint.h>

// This file is heavily influenced by JOS's inc/x86.h.

// TODO(jasonpr): Determine whether this belongs in another file.
struct SegmentSelector {
  // What privileges the CPU must require to use this segment.
  // If the referenced descriptor has a stricter privilege level,
  // then that constraint will be enforced instead.
  unsigned int requested_privilege_level : 2;
  // Which table contains the segment. 0 = GDT, 1 = LDT.
  unsigned int local : 1;
  // The index into the descriptor table.
  unsigned int index : 13;
} __attribute__((packed));

// Usually, we discourage inlining via command line flags. But, we
// want our instruction wrapper functions to be inlined.  So, we mark
// all of them with always_inline.

static __inline uintptr_t get_ebp() __attribute__((always_inline));
static __inline uint8_t inb(uint16_t io_port) __attribute__((always_inline));
static __inline void outb(uint16_t io_port, uint8_t data) __attribute__((always_inline));
static __inline void load_cs(struct SegmentSelector selector) __attribute__((always_inline));
static __inline void load_ds(struct SegmentSelector selector) __attribute__((always_inline));
static __inline void load_es(struct SegmentSelector selector) __attribute__((always_inline));
static __inline void load_fs(struct SegmentSelector selector) __attribute__((always_inline));
static __inline void load_gs(struct SegmentSelector selector) __attribute__((always_inline));
static __inline void load_ss(struct SegmentSelector selector) __attribute__((always_inline));


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

static void load_cs(struct SegmentSelector selector) {
  // Change the CS with a long return.
  // Thanks to Owen at http://f.osdev.org/viewtopic.php?f=1&t=22641

  // Pad the 16-bit selector to 32 bits so it can be pushed onto the
  // stack.
  uint32_t padded_selector = *((uint16_t *) &selector);

  __asm __volatile("push %0\n\t"
		   "push $flush_cs\n\t"
		   "retf\n\t"
		   "flush_cs:" :
		   /* No output. */ :
		   "r" (padded_selector));
}

static void load_ds(struct SegmentSelector selector) {
  __asm __volatile("mov %0, %%ds" :
		   /* No output. */ :
		   "r" (selector));
}

static void load_es(struct SegmentSelector selector) {
  __asm __volatile("mov %0, %%es" :
		   /* No output. */ :
		   "r" (selector));
}

static void load_fs(struct SegmentSelector selector) {
  __asm __volatile("mov %0, %%fs" :
		   /* No output. */ :
		   "r" (selector));
}

static void load_gs(struct SegmentSelector selector) {
  __asm __volatile("mov %0, %%gs" :
		   /* No output. */ :
		   "r" (selector));
}

static void load_ss(struct SegmentSelector selector) {
  __asm __volatile("mov %0, %%ss" :
		   /* No output. */ :
		   "r" (selector));
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
