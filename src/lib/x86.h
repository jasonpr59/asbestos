#ifndef X86_H_
#define X86_H_

#include <segments.h>
#include <stdint.h>

// This file is heavily influenced by JOS's inc/x86.h.

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
static __inline void load_gdt(struct PseudoDescriptor *gdt) __attribute__((always_inline));
static __inline void load_idt(struct PseudoDescriptor *idt) __attribute__((always_inline));
static __inline void enable_interrupts() __attribute__((always_inline));
static __inline void disable_interrupts() __attribute__((always_inline));


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

static void load_gdt(struct PseudoDescriptor *gdt) {
  __asm __volatile("lgdt (%0)" :
		   /* No output. */ :
		   "r" (pseudo_descriptor_address(gdt)));
}

static void load_idt(struct PseudoDescriptor *idt) {
  __asm __volatile("lidt (%0)" :
		   /* No output. */ :
		   "r" (pseudo_descriptor_address(idt)));
}

static void enable_interrupts() {
  __asm __volatile("sti" :
		   /* No output. */ :
		   /* No input. */);
}

static void disable_interrupts() {
  __asm __volatile("cli" :
		   /* No output. */ :
		   /* No input. */);
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
