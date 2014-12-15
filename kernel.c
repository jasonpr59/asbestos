#include "vga.h"

void kernel_initialize() {
  vga_initialize();
  vga_write_string("Starting up TODOS.");

}

void kernel_main() {
  kernel_initialize();
}
