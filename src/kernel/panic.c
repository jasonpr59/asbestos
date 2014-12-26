#include <stdarg.h>
#include "cprintf.h"
#include "backtrace.h"
#include "monitor.h"
#include "panic.h"

// TODO(jasonpr): Use macro magic to add context.
void panic(char *message, ...) {
  cprintf("PANIC: ");

  va_list data;
  va_start(data, message);
  cprintf_var(message, data);

  print_backtrace();
  run_monitor();
}
