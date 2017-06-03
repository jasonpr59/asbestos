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

// Reverse 'string' in place.
char * strrev(char *string) {
  size_t size = strlen(string);
  char saved_left;
  for (unsigned left_index = 0; left_index < size / 2; left_index++) {
    unsigned right_index = size - 1 - left_index;
    saved_left = string[left_index];
    string[left_index] = string[right_index];
    string[right_index] = saved_left;
  }
  return string;
}

int strcmp(const char *a, const char *b) {
  while (1) {
    if (!*a && !*b) {
      return 0;
    } else if (!*a) {
      return -1;
    } else if (!*b) {
      return 1;
    } else if (*a < *b) {
      return -2;
    } else if (*a > *b) {
      return -2;
    } else {
      a++;
      b++;
    }
  }
}
