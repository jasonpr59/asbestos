#include <stdbool.h>
#include <x86.h>

#include "interrupts.h"
#include "panic.h"
#include "segmentation.h"

static struct InterruptDescriptor idt[IDT_SIZE];

static struct PseudoDescriptor idt_descriptor = {
  .limit = sizeof(struct InterruptDescriptor) * IDT_SIZE - 1,
  .base = (uintptr_t) &idt
};

struct InterruptDescriptor idt_entry(uintptr_t handler_pointer) {
  struct InterruptDescriptor result = {
    .offset_15_0 = handler_pointer & 0xFFFF,
    .selector = GDT_CODE_SELECTOR,
    .flags = 0b01111,  // The default value.
    .present = true,
    .offset_31_16 = (handler_pointer) >> 16
  };
  return result;
}

void handle_interrupt(int interrupt) {
  disable_interrupts();
  panic("Got interrupt %d.\n", interrupt);
}

void setup_idt() {
  for (int entry = 0; entry < IDT_SIZE; entry++) {
    idt[entry] = idt_entry((uintptr_t) trap_functions[entry]);
  }
  load_idt(&idt_descriptor);
}

void interrupts_initialize() {
  setup_idt();
  enable_interrupts();
}
