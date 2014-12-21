#include "vga.h"

void vga_demo_scroll() {
  // TODO(jasonpr): Replace with a loop once cprintf is implemented!
  vga_write_string("Demo scroll, line 0.\n");
  vga_write_string("Demo scroll, line 1.\n");
  vga_write_string("Demo scroll, line 2.\n");
  vga_write_string("Demo scroll, line 3.\n");
  vga_write_string("Demo scroll, line 4.\n");
  vga_write_string("Demo scroll, line 5.\n");
  vga_write_string("Demo scroll, line 6.\n");
  vga_write_string("Demo scroll, line 7.\n");
  vga_write_string("Demo scroll, line 8.\n");
  vga_write_string("Demo scroll, line 9.\n");
  vga_write_string("Demo scroll, line 10.\n");
  vga_write_string("Demo scroll, line 11.\n");
  vga_write_string("Demo scroll, line 12.\n");
  vga_write_string("Demo scroll, line 13.\n");
  vga_write_string("Demo scroll, line 14.\n");
  vga_write_string("Demo scroll, line 15.\n");
  vga_write_string("Demo scroll, line 16.\n");
  vga_write_string("Demo scroll, line 17.\n");
  vga_write_string("Demo scroll, line 18.\n");
  vga_write_string("Demo scroll, line 19.\n");
  vga_write_string("Demo scroll, line 20.\n");
  vga_write_string("Demo scroll, line 21.\n");
  vga_write_string("Demo scroll, line 22.\n");
  vga_write_string("Demo scroll, line 23.\n");
  vga_write_string("Demo scroll, line 24.\n");
  vga_write_string("Demo scroll, line 25.\n");
  vga_write_string("Demo scroll, line 26.\n");
  vga_write_string("Demo scroll, line 27.\n");
  vga_write_string("Demo scroll, line 28.\n");
  vga_write_string("Demo scroll, line 29.\n");
  vga_write_string("Demo scroll, line 30.\n");
}

void kernel_initialize() {
  vga_initialize();
  vga_write_string("Starting up Asbestos.");
  // TODO(jasonpr): Remove this demo once scrolling is well-established.
  vga_demo_scroll();
}

void kernel_main() {
  kernel_initialize();
}
