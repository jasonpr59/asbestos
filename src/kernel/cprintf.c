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
  cprintf_var(format, data);
}

void cprintf_var(char *format, va_list data) {
  emit_formatted_var(cprint_char, format, data);
}
