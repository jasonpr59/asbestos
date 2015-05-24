#ifndef ASBESTOS_KERNEL_KEYBOARD_H_
#define ASBESTOS_KERNEL_KEYBOARD_H_

#include <stdbool.h>

void keyboard_initialize();
char keyboard_read();
bool keyboard_has_output();
char keyboard_consume_keypress();

#endif  // ASBESTOS_KERNEL_KEYBOARD_H_
