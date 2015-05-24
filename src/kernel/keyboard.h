#ifndef ASBESTOS_KERNEL_KEYBOARD_H_
#define ASBESTOS_KERNEL_KEYBOARD_H_

void keyboard_initialize();
int keyboard_read(char *output);
char keyboard_consume_keypress();

#endif  // ASBESTOS_KERNEL_KEYBOARD_H_
