#ifndef ASBESTOS_STRING_H_
#define ASBESTOS_STRING_H_

#include <stddef.h>

void * memmove(void *dest, const void *src, size_t count);
size_t strlen(const char *string);
char * strrev(char *string);
int strcmp (const char *a, const char *b);

#endif  // ASBESTOS_STRING_H_
