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

// "Operation Command Words."
#define PIC_OCW2_EOI 0x20

void disable_pics() {
  // Write a fully set bitmask to both PICs, so no hardware interrupts
  // come through.
  // TODO(jasonpr): Move PIC-related code elsewhere.
  outb(PIC_MASTER_DATA, 0xFF);
  outb(PIC_SLAVE_DATA, 0xFF);
}
void pic_send_eoi() {
  // For now, assume the the interrupt came from the master, and
  // only send the eoi to the master.
  // TODO(jasonpr): Handle slave-initiated interrupts.
  outb(PIC_MASTER_CMD, PIC_OCW2_EOI);
}
