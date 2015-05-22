#include <x86.h>
#include "pic.h"

#define PIC_MASTER 0x20
#define PIC_MASTER_CMD PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER + 1)

#define PIC_SLAVE 0xA0
#define PIC_SLAVE_CMD PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)

void disable_pics() {
  // Write a fully set bitmask to both PICs, so no hardware interrupts
  // come through.
  // TODO(jasonpr): Move PIC-related code elsewhere.
  outb(PIC_MASTER_DATA, 0xFF);
  outb(PIC_SLAVE_DATA, 0xFF);
}
