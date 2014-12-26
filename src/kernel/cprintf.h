#ifndef CPRINTF_H_
#define CPRINTF_H_

#include <stdarg.h>

void cprint_char(char character);
void cprintf(char *format, ...);
void cprintf_var(char *format, va_list args);

#endif  // CPRINTF_H_
