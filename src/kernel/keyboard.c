// This file implements keyboard control.

// Useful resources include:
//  * zet.aluzina.org/images/d/d4/8042.pdf
//  * stanislavs.org/helppc/8042.html
//  * The IBM PC AT Technical Reference (1502494), available online at
//    ia801607.us.archive.org/30/items/bitsavers_ibmpcat150ferenceMar84_26847525/1502494_PC_AT_Technical_Reference_Mar84.pdf

#include <stdbool.h>
#include <stddef.h>
#include <x86.h>
#include "cprintf.h"
#include "input.h"
#include "panic.h"
#include "keyboard.h"

#define KEYBOARD_DATA_IO_PORT 0x60
#define KEYBOARD_STATUS_IO_PORT 0x64
#define KEYBOARD_COMMAND_IO_PORT 0x64

#define KEYBOARD_OUTPUT_BUFFER_FULL 0x1
#define KEYBOARD_INPUT_BUFFER_FULL 0x2

#define KEYBOARD_SELF_TEST_COMMAND 0xAA
#define KEYBOARD_SELF_TEST_EXPECTED_RESULT 0x55

#define KEYBOARD_INTERFACE_TEST_COMMAND 0xAB
#define KEYBOARD_INTERFACE_TEST_EXPECTED_RESULT 0x00

static const char kScancodeLeftShiftPressed = 0x2A;
static const char kScancodeLeftShiftReleased = 0xAA;
static const char kScancodeRightShiftPressed = 0x36;
static const char kScancodeRightShiftReleased = 0xB6;

static char key_to_ascii[256] =
{
  0x0, 0x0, '1', '2', '3', '4', '5', '6',
  '7', '8', '9', '0', '-', '=', 0x0, 0x0,
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
  'o', 'p', '[', ']', '\n', 0x0, 'a', 's',
  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  '\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',
  'b', 'n', 'm', ',', '.', '/', 0x0, '*',
  0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',
  '8', '9', '-', '4', '5', '6', '+', '1', 
  '2', '3', '0', '.'
};

static char key_to_ascii_shift[256] =
{
  0x0, 0x0, '!', '@', '#', '$', '%', '^',
  '&', '*', '(', ')', '_', '+', 0x0, 0x0,
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
  'O', 'P', '{', '}', '\n', 0x0, 'A', 'S',
  'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  '"', '~', 0x0, '|', 'Z', 'X', 'C', 'V',
  'B', 'N', 'M', '<', '>', '?', 0x0, '*',
  0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',
  '8', '9', '-', '4', '5', '6', '+', '1', 
  '2', '3', '0', '.'
};

// Keyboard state.
static bool left_shift_pressed = false; 
static bool right_shift_pressed = false; 

void spin_until_input_buffer_empty() {
  while (inb(KEYBOARD_STATUS_IO_PORT) & KEYBOARD_INPUT_BUFFER_FULL) {
    // Do nothing.  Just spin.
  }
}

void spin_until_output_buffer_full() {
  while (!(inb(KEYBOARD_STATUS_IO_PORT) & KEYBOARD_OUTPUT_BUFFER_FULL)) {
    // Do nothing.  Just spin.
  }
}

void keyboard_write_command(char command) {
  spin_until_input_buffer_empty();
  outb(KEYBOARD_COMMAND_IO_PORT, command);
}

char keyboard_read_data() {
  spin_until_output_buffer_full();
  return inb(KEYBOARD_DATA_IO_PORT);
}

void keyboard_self_test() {
  keyboard_write_command(KEYBOARD_SELF_TEST_COMMAND);
  char self_test_result = keyboard_read_data();
  if (self_test_result != KEYBOARD_SELF_TEST_EXPECTED_RESULT) {
    panic("[KEYBOARD] Failed self test.\n");
  }
}

void keyboard_interface_test() {
  keyboard_write_command(KEYBOARD_INTERFACE_TEST_COMMAND);
  char interface_test_result = keyboard_read_data();
  if (interface_test_result != KEYBOARD_INTERFACE_TEST_EXPECTED_RESULT) {
    panic("[KEYBOARD] Failed interface test.\n");
  }
}

void keyboard_initialize() {
  keyboard_self_test();
  keyboard_interface_test();
}

int keyboard_read(char *output) {
  if (!(inb(KEYBOARD_STATUS_IO_PORT) & KEYBOARD_OUTPUT_BUFFER_FULL)) {
    return INPUT_EXHAUSTED;
  }

  char scancode = keyboard_read_data();
  if (scancode == kScancodeLeftShiftPressed) {
    left_shift_pressed = true;
  } else if (scancode == kScancodeLeftShiftReleased) {
    left_shift_pressed = false;
  } else if (scancode == kScancodeRightShiftPressed) {
    right_shift_pressed = true;
  } else if (scancode == kScancodeRightShiftReleased) {
    right_shift_pressed = false;
  }
  size_t scancode_index = (size_t) scancode;
  char ascii_character = (left_shift_pressed || right_shift_pressed)
      ? key_to_ascii_shift[scancode_index]
      : key_to_ascii[scancode_index];
  if (ascii_character) {
    *output = ascii_character;
    return 0;
  } else {
    // This keypress did not yield a character.
    return INPUT_RETRY;
  }
}
