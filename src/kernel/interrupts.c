#include <stdbool.h>
#include <x86.h>

#include "interrupts.h"
#include "cprintf.h"
#include "panic.h"
#include "pic.h"
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

void print_trap_frame(struct TrapFrame *trap_frame) {
  cprintf("Got trap %d from EIP 0x%08x.\n",
	  trap_frame->interrupt_number, trap_frame->cpu_frame.eip);
}

void handle_interrupt(struct TrapFrame trap_frame) {
  switch (trap_frame.interrupt_number) {
  case INTERRUPT_DIVIDE_ERROR:
    panic("Divide error.\n");
    break;
  case INTERRUPT_DEBUG_EXCEPTION:
    panic("Debug error.\n");
    break;
  case INTERRUPT_NMI:
    panic("Non-maskable interrupt.\n");
    break;
  case INTERRUPT_BREAKPOINT:
    panic("Breakpoint.\n");
    break;
  case INTERRUPT_OVERFLOW:
    panic("Overflow.\n");
    break;
  case INTERRUPT_BOUNDS_CHECK:
    panic("Failed bounds check.\n");
    break;
  case INTERRUPT_INVALID_OPCODE:
    panic("Invalid opcode.\n");
    break;
  case INTERRUPT_COPROCESSOR_NOT_AVAILABLE:
    panic("Coprocessor not available.\n");
    break;
  case INTERRUPT_DOUBLE_FAULT:
    panic("Double fault.\n");
    break;
  case INTERRUPT_RESERVED_9:
    panic("Reserved interrupt (9).\n");
    break;
  case INTERRUPT_INVALID_TSS:
    panic("Invalid TSS.\n");
    break;
  case INTERRUPT_SEGMENT_NOT_PRESENT:
    panic("Segment not present.\n");
    break;
  case INTERRUPT_STACK_EXCEPTION:
    panic("Stack exception.\n");
    break;
  case INTERRUPT_GENERAL_PROTECTION_FAULT:
    panic("General protection fault.\n");
    break;
  case INTERRUPT_PAGE_FAULT:
    panic("Page fault.\n");
    break;
  case INTERRUPT_RESERVED_15:
    panic("Reserved interrupt (15).\n");
    break;
  case INTERRUPT_COPROCESSOR_ERROR:
    panic("Coprocessor error.\n");
    break;
  case INTERRUPT_PASS_THROUGH:
    cprintf("Handling pass-through interrupt.\n");
    break;
  case INTERRUPT_SYSCALL:
    panic("Syscall.\n");
    break;
  default:
    panic("Unidentified interrupt: %d.\n", trap_frame.interrupt_number);
    break;
  }
}

void setup_idt() {
  for (int entry = 0; entry < IDT_SIZE; entry++) {
    idt[entry] = idt_entry((uintptr_t) trap_functions[entry]);
  }
  load_idt(&idt_descriptor);
}

void interrupts_initialize() {
  disable_pics();
  setup_idt();
  enable_interrupts();
}
