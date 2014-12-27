#include <x86.h>
#include "cprintf.h"
#include "monitor.h"
#include "multiboot.h"
#include "panic.h"
#include "keyboard.h"
#include "serial.h"
#include "vga.h"

void kernel_initialize_terminal() {
  serial_initialize();
  vga_initialize();
  keyboard_initialize();
}

void kernel_validate_multiboot_handoff(uint32_t handoff_eax) {
  if (handoff_eax != MULTIBOOT_HANDOFF_EAX) {
    panic("[MULTIBOOT] Bad handoff %%eax value: 0x%08x.\n",handoff_eax);
  } else {
    cprintf("Multiboot handoff completed successfully.\n");
  }
}

void kernel_main(struct PushedRegisters registers) {
  kernel_initialize_terminal();
  cprintf("Starting up Asbestos.\n");
  kernel_validate_multiboot_handoff(registers.eax);
  run_monitor();
}
