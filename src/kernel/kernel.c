#include "cprintf.h"
#include "vga.h"

void vga_demo_scroll() {
  for (int i = 0; i < 30; i++) {
    cprintf("Demo scroll, line 0x%02x.\n", i);
  }
}

void demo_cprintf() {
  cprintf("The hex number 0x%x is twenty.\n", 20);
  cprintf("The word '%5s' means '%15s' in Spanish.\n",
	  "hola", "hello");
  cprintf("The word '%s' means '%s' in Spanish.\n",
	  "lapiz", "pencil");
}

void kernel_initialize() {
  vga_initialize();
  // TODO(jasonpr): Remove this demo once scrolling is well-established.
  vga_demo_scroll();
  cprintf("Starting up Asbestos.\n");
  demo_cprintf();
}

void kernel_main() {
  kernel_initialize();
}
