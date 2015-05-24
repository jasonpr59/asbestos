#include "read.h"

char * read_string(char (*read_character)(), char *buffer, size_t buffer_size){
  size_t index = 0;
  while (index < buffer_size - 1) {
    char input = read_character();
    buffer[index++] = input;
    // TODO(jasonpr): Allow \r\n to be read as a single "enter".
    if (input == '\n' || input == '\r') {
      break;
    }
  }
  buffer[index] = 0;
  return buffer;
}
