#include "print.h"

void emit_formatted(void (*emit)(char), char *format, ...) {
  va_list data;
  va_start(data, format);
  emit_formatted_var(emit, format, data);
  va_end(data);
}

void emit_formatted_var(void (*emit)(char), char *format, va_list data) {
  // TODO(jasonpr): Actually do some formatting!
  while (*format) {
    emit(*format);
    format++;
  }
}  
