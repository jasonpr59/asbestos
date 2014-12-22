#include "cprintf.h"
#include "vga.h"

void vga_demo_scroll() {
  // TODO(jasonpr): Replace with a loop once cprintf is implemented!
  cprintf("Demo scroll, line 0.\n");
  cprintf("Demo scroll, line 1.\n");
  cprintf("Demo scroll, line 2.\n");
  cprintf("Demo scroll, line 3.\n");
  cprintf("Demo scroll, line 4.\n");
  cprintf("Demo scroll, line 5.\n");
  cprintf("Demo scroll, line 6.\n");
  cprintf("Demo scroll, line 7.\n");
  cprintf("Demo scroll, line 8.\n");
  cprintf("Demo scroll, line 9.\n");
  cprintf("Demo scroll, line 10.\n");
  cprintf("Demo scroll, line 11.\n");
  cprintf("Demo scroll, line 12.\n");
  cprintf("Demo scroll, line 13.\n");
  cprintf("Demo scroll, line 14.\n");
  cprintf("Demo scroll, line 15.\n");
  cprintf("Demo scroll, line 16.\n");
  cprintf("Demo scroll, line 17.\n");
  cprintf("Demo scroll, line 18.\n");
  cprintf("Demo scroll, line 19.\n");
  cprintf("Demo scroll, line 20.\n");
  cprintf("Demo scroll, line 21.\n");
  cprintf("Demo scroll, line 22.\n");
  cprintf("Demo scroll, line 23.\n");
  cprintf("Demo scroll, line 24.\n");
  cprintf("Demo scroll, line 25.\n");
  cprintf("Demo scroll, line 26.\n");
  cprintf("Demo scroll, line 27.\n");
  cprintf("Demo scroll, line 28.\n");
  cprintf("Demo scroll, line 29.\n");
  cprintf("Demo scroll, line 30.\n");
}

void kernel_initialize() {
  vga_initialize();
  // TODO(jasonpr): Remove this demo once scrolling is well-established.
  vga_demo_scroll();
  cprintf("Starting up Asbestos.\n");
  cprintf("The hex number %x is twenty.\n", 20);
  cprintf("The word '%5s' means '%15s' in Spanish.\n",
	  "hola", "hello");
}

void kernel_main() {
  kernel_initialize();
}
