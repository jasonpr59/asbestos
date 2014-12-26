#include "backtrace.h"
#include "cprintf.h"
#include "monitor.h"
#include "keyboard.h"
#include "serial.h"
#include "vga.h"

void vga_demo_scroll() {
  for (int i = 0; i < 30; i++) {
    cprintf("Demo scroll, line % 2d (0x%02x).\n", i, i);
  }
}

void demo_cprintf() {
  cprintf("The hex number 0x%x is twenty.\n", 20);
  cprintf("The word '%5s' means '%15s' in Spanish.\n",
	  "hola", "hello");
  cprintf("The word '%s' means '%s' in Spanish.\n",
	  "lapiz", "pencil");
}

void demo_backtrace(int depth) {
  if (depth <= 0) {
    cprintf("Early backtrace:\n");
    print_backtrace();
    cprintf("\n");
    cprintf("Late backtrace: \n");
    print_backtrace();
    cprintf("\n");
  } else {
    demo_backtrace(depth - 1);
  }
}

void kernel_initialize() {
  serial_initialize();
  vga_initialize();
  keyboard_initialize();
  // TODO(jasonpr): Remove this demo once scrolling is well-established.
  vga_demo_scroll();
  cprintf("Starting up Asbestos.\n");
  demo_cprintf();
  demo_backtrace(5);
}

void kernel_main() {
  kernel_initialize();
  run_monitor();
}
