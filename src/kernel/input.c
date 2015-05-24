#include <read.h>
#include <ringbuffer.h>
#include "cprintf.h"
#include "input.h"
#include "panic.h"

#define CHARACTER_RING_SIZE 100

static char character_ring_space[CHARACTER_RING_SIZE];
static struct RingBuffer character_buffer = {
  character_ring_space,
  CHARACTER_RING_SIZE,
  0,
  0
};

int read_all_input(int (*input_read)(char *output)) {
  while (!ring_buffer_full(&character_buffer)) {
    char input;
    int result = input_read(&input);
    if (result == 0) {
      ring_buffer_append(&character_buffer, input);
    } else if (result == INPUT_RETRY) {
      continue;
    } else if (result == INPUT_EXHAUSTED) {
      return 0;
    } else {
      panic("[INPUT] Unexpected input_read() result: 0x%02x\n", result);
    }
  }
  return ERR_INPUT_BUFFER_FULL;
}

char input_character() {
  while (ring_buffer_empty(&character_buffer)) {
    // Spin until an interrupt handler feeds the buffer.
  }
  char input = ring_buffer_pop(&character_buffer);

  // TODO(jasonpr): Decide on a good time to do newline conversions.
  // This will involve determining which functions should return the
  // raw data they get from the hardware, and which ones should expose
  // a consistent interface.
  // Since we use '\n' as a full line ending in vga.c, this
  // conversion works.  But, it's hacky.
  if (input == '\r') {
    input = '\n';
  }
  cprint_char(input);
  return input;
}

char * input_string(char *buffer, size_t buffer_size) {
  return read_string(input_character, buffer, buffer_size);
}
