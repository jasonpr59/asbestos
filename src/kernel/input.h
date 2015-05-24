#ifndef ASBESTOS_KERNEL_INPUT_H_
#define ASBESTOS_KERNEL_INPUT_H_

#include <stddef.h>

int get_keyboard_input();
int get_serial_input();
char input_character();
char * input_string(char *buffer, size_t buffer_size);

#endif // ASBESTOS_KERNEL_INPUT_H_
