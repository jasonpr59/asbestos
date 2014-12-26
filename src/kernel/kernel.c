#include "cprintf.h"
#include "monitor.h"
#include "keyboard.h"
#include "serial.h"
#include "vga.h"

void kernel_initialize() {
  serial_initialize();
  vga_initialize();
  keyboard_initialize();
  cprintf("Starting up Asbestos.\n");
}

void kernel_main() {
  kernel_initialize();
  run_monitor();
}
