#include "string.h"

void* memmove(void *dest, const void *src, size_t count) {
  char *src_char = (char *) src;
  char *dest_char = (char *) dest;

  char *from;
  char *to;
  if (src >= dest) {
    // Copy front-to-back.
    from = src_char;
    to = dest_char;
    while (from < src_char + count) {
      *to++ = *from++;
    }
  } else {
    // Copy back-to-front.
    from = src_char + count - 1;
    to = dest_char + count - 1;
    while (from >= src_char) {
      *to-- = *from--;
    }
  }
  return dest;
}

size_t strlen(const char *string) {
  char *current = (char *) string;
  int size = 0;
  while (*current++) {
    size++;
  }
  return size;
}
