#include "read.h"

char * read_string(char (*read_character)(), char *buffer, size_t buffer_size){
  size_t index = 0;
  while (index < buffer_size - 1) {
    char input = read_character();
    buffer[index++] = input;
    if (input == '\n') {
      break;
    }
  }
  buffer[index] = 0;
  return buffer;
}
