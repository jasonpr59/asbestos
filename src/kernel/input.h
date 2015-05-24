#ifndef ASBESTOS_KERNEL_INPUT_H_
#define ASBESTOS_KERNEL_INPUT_H_

#include <stddef.h>

#define ERR_INPUT_BUFFER_FULL -1

// Return values for `$INPUT_read()` functions:

// The call to a input read function failed because there is no more
// input to consume at the moment.
#define INPUT_EXHAUSTED -1
// The call to an input read function did not produce any data.  There
// still may be more input to consume.  (For example, the function
// might have read a key-up event, which produces no character data.)
#define INPUT_RETRY -2


int read_all_input(int (*input_read)(char *output));
char input_character();
char * input_string(char *buffer, size_t buffer_size);

#endif // ASBESTOS_KERNEL_INPUT_H_
