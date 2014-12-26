#include "cprintf.h"
#include "monitor.h"
#include "keyboard.h"
#include "serial.h"
#include "vga.h"

void kernel_initialize_terminal() {
  serial_initialize();
  vga_initialize();
  keyboard_initialize();
}

void kernel_main() {
  kernel_initialize_terminal();
  cprintf("Starting up Asbestos.\n");
  run_monitor();
}
