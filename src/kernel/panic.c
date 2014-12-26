#include <stdarg.h>
#include "cprintf.h"
#include "backtrace.h"
#include "monitor.h"
#include "panic.h"

// TODO(jasonpr): Use macro magic to add context.
void _panic(const char  *file, int line, const char *function, char *message, ...) {
  cprintf("Panic in %s() at %s:%d.\n", function, file, line);

  va_list data;
  va_start(data, message);
  cprintf_var(message, data);

  print_backtrace();
  run_monitor();
}
