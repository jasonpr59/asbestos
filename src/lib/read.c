#include "read.h"

char * read_string(char (*read_character)(), char *buffer, size_t buffer_size,
		   void (*write_character)(char)){
  size_t index = 0;
  while (index < buffer_size - 1) {
    char input = read_character();
    // TODO(jasonpr): Decide on either \n or \r as the Asbestos
    // standard, and require the input source to do its own
    // conversions for plaintext input.
    if (input == '\n' || input == '\r') {
      write_character('\n');
      break;
    } else {
      write_character(input);
    }
    // Do not put newlines into the buffer.
    buffer[index++] = input;
  }
  buffer[index] = 0;
  return buffer;
}
