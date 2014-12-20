#include "vga.h"

void vga_demo_scroll() {
  // TODO(jasonpr): Replace with a loop once cprintf is implemented!
  vga_write_string("Demo scroll, line 0.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 1.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 2.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 3.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 4.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 5.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 6.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 7.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 8.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 9.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 10.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 11.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 12.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 13.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 14.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 15.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 16.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 17.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 18.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 19.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 20.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 21.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 22.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 23.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 24.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 25.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 26.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 27.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 28.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 29.");
  vga_write_newline();
  vga_write_string("Demo scroll, line 30.");
  vga_write_newline();
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
