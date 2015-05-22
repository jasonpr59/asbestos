#include <stdint.h>
#include <x86.h>
#include "interrupts.h"
#include "pic.h"

#define PIC_MASTER 0x20
#define PIC_MASTER_CMD PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER + 1)

#define PIC_SLAVE 0xA0
#define PIC_SLAVE_CMD PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)

// "Initialization Command Words."
#define PIC_ICW1_IC4 0x01  // Whether we send a fourth ICW.
#define PIC_ICW1_SNGL 0x02  // Set if the PIC has no slave.
#define PIC_ICW1_MAGIC_BIT 0x10  // Indicates that this is ICW1.

#define PIC_ICW4_8086_MODE 0x01  // The PIC should operate in 8086 mode.

// "Operation Command Words."
#define PIC_OCW2_EOI 0x20

// Master PIC mask bits.
#define PIC_TIMER_MASK (1 << TIMER_IR_LINE)
#define PIC_KEYBOARD_MASK (1 << KEYBOARD_IR_LINE)
#define PIC_COM1_MASK (1 << COM1_IR_LINE)
#define PIC_COM2_MASK (1 << COM2_IR_LINE)

void disable_pics() {
  // Write a fully set bitmask to both PICs, so no hardware interrupts
  // come through.
  outb(PIC_MASTER_DATA, 0xFF);
  outb(PIC_SLAVE_DATA, 0xFF);
}

void enable_pics() {
  uint8_t icw1 = PIC_ICW1_MAGIC_BIT | PIC_ICW1_SNGL | PIC_ICW1_IC4;
  outb(PIC_MASTER_CMD, icw1);

  uint8_t icw2 = EXTERNAL_INTERRUPT_OFFSET & 0xF8;
  outb(PIC_MASTER_DATA, icw2);

  // Skip icw3, since we have set PIC_ICW1_SNGL.

  uint8_t icw4 = PIC_ICW4_8086_MODE;
  outb(PIC_MASTER_DATA, icw4);

  // Enable some interrupts by unmasking them.
  uint8_t pic_master_mask = ~(PIC_TIMER_MASK |
			      PIC_KEYBOARD_MASK |
			      PIC_COM1_MASK);
  outb(PIC_MASTER_DATA, pic_master_mask);
  outb(PIC_SLAVE_DATA, 0xFF);
}

void pic_send_eoi() {
  // For now, assume the the interrupt came from the master, and
  // only send the eoi to the master.
  // TODO(jasonpr): Handle slave-initiated interrupts.
  outb(PIC_MASTER_CMD, PIC_OCW2_EOI);
}
