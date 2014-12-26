#include <stdarg.h>
#include <print.h>
#include "cprintf.h"
#include "serial.h"
#include "vga.h"

void cprint_char(char character) {
  vga_write(character);
  serial_write(character);
}

void cprintf(char *format, ...) {
  va_list data;
  va_start(data, format);
  emit_formatted_var(cprint_char, format, data);
}
