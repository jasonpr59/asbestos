#include <read.h>
#include "cprintf.h"
#include "input.h"
#include "keyboard.h"

char input_character() {
  char input = keyboard_read();
  cprint_char(input);
  return input;
}

char * input_string(char *buffer, size_t buffer_size) {
  return read_string(input_character, buffer, buffer_size);
}
