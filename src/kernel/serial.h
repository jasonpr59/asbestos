#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdbool.h>

void serial_initialize();
void serial_write(char character);
char serial_read();
bool serial_can_read();

#endif  // SERIAL_H_
