#ifndef ASBESTOS_LIB_READ_H_
#define ASBESTOS_LIB_READ_H_

#include <stddef.h>

char * read_string(char (*read_character)(), char *buffer, size_t buffer_size);

#endif  // ASBESTOS_LIB_READ_H_
