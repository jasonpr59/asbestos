#ifndef SERIAL_H_
#define SERIAL_H_

void serial_initialize();
void serial_write(char character);
int serial_read(char *output);

#endif  // SERIAL_H_
