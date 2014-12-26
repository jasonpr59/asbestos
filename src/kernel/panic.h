#ifndef ASBESTOS_KERNEL_PANIC_H_
#define ASBESTOS_KERNEL_PANIC_H_

#include <stdarg.h>

#define panic(message, ...) _panic(__FILE__, __LINE__, __func__, message, ##__VA_ARGS__)

void _panic(const char *file, int line, const char *function, char *message, ...);

#endif  // ASBESTOS_KERNEL_PANIC_H_
