#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "print.h"

void emit_formatted(void (*emit)(char), char *format, ...) {
  va_list data;
  va_start(data, format);
  emit_formatted_var(emit, format, data);
  va_end(data);
}

// Return whether a character is one of the ten decimal digits.
static bool is_digit(char character) {
  return ('0' <= character && character <= '9');
}

// Convert a decimal digit to an integer.
static int char_to_int(char character) {
  // TODO(jasonpr): Validate input.
  return character - '0';
}

// Convert a string to an integer.
int string_to_int(char *string) {
  int value = 0;
  while (*string) {
    value *= 10;
    value += char_to_int(*string++);
  }
  return value;
}

// Consume up to max_length characters from the stream, where all
// characters are ASCII digits.  Put those characters in buffer,
// followed by a null byte.
void consume_number(char **stream, char *buffer, int max_length) {
  // How many characters we have consumed.
  int consumed = 0;
  // Save room for the null byte!
  while (consumed < max_length) {
    if (!is_digit(**stream)) {
      break;
    }
    *buffer++ = **stream;
    consumed++;
    (*stream)++;
  }
  *buffer = '\0';
}

struct EscapeFlags {
  // How many characters to fill (right justified).
  uint8_t length;
  // What to fill empty space with.
  char fill_character;
  // Which conversion to perform.  'x' for hex, 's' for string, etc.
  char conversion;
};

static const int kMaxFormatLength = 2;
// Parse the escape sequence, starting after the escaping percent
// sign.  The format stream is advanced to the first character after
// the escape sequence.
struct EscapeFlags escape_flags(char **format_stream) {
  struct EscapeFlags flags;
  // If the next character is a space or a zero, then it specifies the
  // fill character.
  if (**format_stream == ' ') {
    flags.fill_character = ' ';
    (*format_stream)++;
  } else if (**format_stream == '0') {
    flags.fill_character = '0';
    (*format_stream)++;
  } else {
    flags.fill_character = ' ';
  }

  char length_buffer[kMaxFormatLength + 1];
  consume_number(format_stream, length_buffer, kMaxFormatLength);
  flags.length = string_to_int(length_buffer);

  // TODO(jasonpr): Determine the best place to validate the
  // conversion.  Probably here.
  flags.conversion = **format_stream;
  // If it's null, don't advance.  We're at the end.
  if (flags.conversion != '\0') {
    (*format_stream)++;
  }
  return flags;
}

void emit_padded_buffer(void (*emit)(char), char *buffer, char filler,
			size_t fill_to) {
  unsigned data_length = strlen(buffer);
  int padding_size = fill_to - data_length;
  for (int i = 0; i < padding_size; i++) {
    emit(filler);
  }
  while (*buffer) {
    emit(*buffer++);
  }
}

// Convert a number to a character digit..
// The order of digits is "01...89ab...yz".
// Behavior is undefined if digit > 35 or digit < 0.
static char character_digit(int digit) {
  if (0 <= digit && digit <= 9) {
    return '0' + digit;
  }
  return 'a' + digit - 10;
}

void fill_buffer_with_radix(char *buffer, unsigned value, int radix) {
  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }

  // We start out working on the radix^0's place.
  int exponent = 0;
  while (value != 0) {
    int digit = value % radix;
    value = (value - digit) / radix;
    buffer[exponent++] = character_digit(digit);
  }
  buffer[exponent] = '\0';
  strrev(buffer);
}

// Assuming 32-bit numbers, we need 8 hex digits plus a null byte.
static const size_t kHexBufferSize = 9;
// We need 10 decimal digits plus a null byte.
static const size_t kDecimalBufferSize = 11;

// Emit the data for the current escape sequence, partly consuming the
// format and data streams.
void emit_datum(void (*emit)(char), char **format_stream,
		va_list *data_stream) {
  if (**format_stream == '%') {
    // It's just an escaped percent sign.
    emit('%');
    (*format_stream)++;
    return;
  }
  struct EscapeFlags flags = escape_flags(format_stream);
  if (flags.conversion == 'x') {
    // Emit as hex.
    unsigned value = va_arg(*data_stream, unsigned);
    char hex_buffer[kHexBufferSize];
    fill_buffer_with_radix(hex_buffer, value, 16);
    emit_padded_buffer(emit, hex_buffer, flags.fill_character, flags.length);
  } else if (flags.conversion == 'd') {
    // Emit as decimal.
    unsigned value = va_arg(*data_stream, unsigned);
    char decimal_buffer[kDecimalBufferSize];
    fill_buffer_with_radix(decimal_buffer, value, 10);
    emit_padded_buffer(emit, decimal_buffer, flags.fill_character,
		       flags.length);
  } else if (flags.conversion == 's') {
    // Emit string.
    char *string = va_arg(*data_stream, char *);
    emit_padded_buffer(emit, string, flags.fill_character, flags.length);
  } else {
    // TODO(jasonpr): Throw an error.
  }
}

void emit_formatted_var(void (*emit)(char), char *format, va_list data) {
  char *next_char = format;
  while (*next_char) {
    if (*next_char == '%') {
      next_char++;
      emit_datum(emit, &next_char, &data);
      continue;
    }
    emit(*next_char++);
  }
}  
