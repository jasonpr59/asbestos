#include "read.h"

char * read_string(char (*read_character)(), char *buffer, size_t buffer_size,
		   void (*write_character)(char)){
  size_t index = 0;
  while (index < buffer_size - 1) {
    char input = read_character();
    // The Asbestos standard is that \n is a newline, but we'll accept
    // \r as an EOL character.
    // TODO(jasonpr): Also accept CRLF or LFCR as a newline character
    // pair, and don't return before consuming the second half of this
    // nonconforming newline.
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
