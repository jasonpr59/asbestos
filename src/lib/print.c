#include "print.h"

void emit_formatted(void (*emit)(char), char *format, ...) {
  va_list data;
  va_start(data, format);
  emit_formatted_var(emit, format, data);
  va_end(data);
}

// Emit the data for the current escape sequence, partly consuming the
// format and data streams.
void emit_datum(void (*emit)(char), char *format_stream,
		va_list data_stream) {
  char data_type = *format_stream++;
  switch (data_type) {
  case '%':
    // It's just an escaped percent sign.
    emit('%');
    return;
  case 'x':
    // Emit as hex.
    // TODO(jasonpr): Implement.
    return;
  case 's':
    // Emit string.
    // TODO(jasonpr): Implement.
    return;
  default:
    // TODO(jasonpr): Throw an error.
    return;
  }
}

void emit_formatted_var(void (*emit)(char), char *format, va_list data) {
  char *next_char = format;
  while (*next_char) {
    if (*next_char == '%') {
      next_char++;
      emit_datum(emit, next_char, data);
      continue;
    }
    emit(*next_char++);
  }
}  
