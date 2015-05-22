#ifndef ASBESTOS_KERNEL_INTERRUPTS_H_
#define ASBESTOS_KERNEL_INTERRUPTS_H_

#include <stdint.h>
#include <x86.h>

// Useful resources:
// http://www.intel.com/design/pentium/manuals/24143004.pdf
// https://css.csail.mit.edu/6.858/2010/readings/i386.pdf

// Intel-specified Interrupts:
#define INTERRUPT_DIVIDE_ERROR 0
#define INTERRUPT_DEBUG_EXCEPTION 1
#define INTERRUPT_NMI 2
#define INTERRUPT_BREAKPOINT 3
#define INTERRUPT_OVERFLOW 4
#define INTERRUPT_BOUNDS_CHECK 5
#define INTERRUPT_INVALID_OPCODE 6
#define INTERRUPT_COPROCESSOR_NOT_AVAILABLE 7
#define INTERRUPT_DOUBLE_FAULT 8
#define INTERRUPT_RESERVED_9 9
#define INTERRUPT_INVALID_TSS 10
#define INTERRUPT_SEGMENT_NOT_PRESENT 11
#define INTERRUPT_STACK_EXCEPTION 12
#define INTERRUPT_GENERAL_PROTECTION_FAULT 13
#define INTERRUPT_PAGE_FAULT 14
#define INTERRUPT_RESERVED_15 15
#define INTERRUPT_COPROCESSOR_ERROR 16

// External Interrupts:
#define EXTERNAL_INTERRUPT_OFFSET 32
#define TIMER_IR_LINE 0
#define KEYBOARD_IR_LINE 1
#define CASCADE_IR_LINE 2
#define COM2_IR_LINE 3
#define COM1_IR_LINE 4
#define LPT2_IR_LINE 5
#define FLOPPY_IR_LINE 6
#define SPURIOUS_IR_LINE 7
#define CMOS_RTC_IR_LINE 8
#define MOUSE_IR_LINE 12
#define COPROCESSOR_IR_LINE 13
#define ATA1_IR_LINE 14
#define ATA2_IR_LINE 15

#define INTERRUPT_TIMER (EXTERNAL_INTERRUPT_OFFSET + TIMER_IR_LINE)
#define INTERRUPT_KEYBOARD (EXTERNAL_INTERRUPT_OFFSET + KEYBOARD_IR_LINE)
#define INTERRUPT_CASCADE (EXTERNAL_INTERRUPT_OFFSET + CASCADE_IR_LINE)  // Never raised
#define INTERRUPT_COM2 (EXTERNAL_INTERRUPT_OFFSET + COM2_IR_LINE)
#define INTERRUPT_COM1 (EXTERNAL_INTERRUPT_OFFSET + COM1_IR_LINE)
#define INTERRUPT_LPT2 (EXTERNAL_INTERRUPT_OFFSET + LPT2_IR_LINE)
#define INTERRUPT_FLOPPY (EXTERNAL_INTERRUPT_OFFSET + FLOPPY_IR_LINE)
#define INTERRUPT_SPURIOUS (EXTERNAL_INTERRUPT_OFFSET + SPURIOUS_IR_LINE)
#define INTERRUPT_CMOS_RTC (EXTERNAL_INTERRUPT_OFFSET + CMOS_RTC_IR_LINE)
#define INTERRUPT_MOUSE (EXTERNAL_INTERRUPT_OFFSET + MOUSE_IR_LINE)
#define INTERRUPT_COPROCESSOR (EXTERNAL_INTERRUPT_OFFSET + COPROCESSOR_IR_LINE)
#define INTERRUPT_ATA1 (EXTERNAL_INTERRUPT_OFFSET + ATA1_IR_LINE)
#define INTERRUPT_ATA2 (EXTERNAL_INTERRUPT_OFFSET + ATA2_IR_LINE)

// Custom software interrupts:
#define INTERRUPT_PASS_THROUGH 50
#define INTERRUPT_SYSCALL 60
#define IDT_SIZE 62

// An InterruptDescriptor is a "Trap Gate" from page 157 of the i386
// manual.  The author of
// http://littleosbook.github.io/#interrupts-handlers recommends using
// this type of gate (not a task gate or an interrupt gate).
struct InterruptDescriptor {
  uint16_t offset_15_0;
  struct SegmentSelector selector;
  unsigned int unused_1 : 5;
  unsigned int zeroes_1 : 3;
  // The manual doesn't explain these flags.
  // It only specifies that they must have values 0b01111.
  unsigned int flags : 5;
  unsigned int privilege_level : 2;
  unsigned int present : 1;
  uint16_t offset_31_16;
} __attribute__((packed));


struct CpuExceptionFrame {
  uint32_t error_code;
  uintptr_t eip;
  uint16_t cs;
  uint16_t padding_1;
  uint16_t eflags;
};

struct TrapFrame {
  struct PushedRegisters pushed_registers;
  uint32_t interrupt_number;
  struct CpuExceptionFrame cpu_frame;
};

void interrupts_initialize();
void handle_interrupt();

extern const uintptr_t trap_functions[];

#endif  // ASBESTOS_KERNEL_INTERRUPTS_H_
