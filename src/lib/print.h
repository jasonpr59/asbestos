#ifndef PRINT_H_
#define PRINT_H_

#include <stdarg.h>

// I'm deliberately ignoring the standard printing-related functions.
// I will let these stand-in functions grow organically.  I expect
// they will grow similar to the standard functions, with time.
//  TODO(jasonpr): Make these functions conform to standards.

void emit_formatted(void (*emit)(char), char *format, ...);
void emit_formatted_var(void (*emit)(char), char *format, va_list data);

#endif  // CPRINTF_H_
