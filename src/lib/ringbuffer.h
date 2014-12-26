#ifndef ASBESTOS_LIB_RINGBUFFER_H_
#define ASBESTOS_LIB_RINGBUFFER_H_

#include <stdbool.h>
#include <stddef.h>

struct RingBuffer {
  char *buffer;
  // Maximum capacity is size - 1.
  size_t size;
  int head;
  int tail;
};

// Get the number of elements currently in the ring buffer.
size_t ring_buffer_population(struct RingBuffer *ring_buffer);

bool ring_buffer_full(struct RingBuffer *ring_buffer);
bool ring_buffer_empty(struct RingBuffer *ring_buffer);

// Add a character to the tail of the ring buffer.  Fails if the ring
// buffer is already at maximum capacity.
// Returns 0 if the operation succeeds, -1 otherwise.
int ring_buffer_append(struct RingBuffer *ring_buffer, char value);

// Returns the value at the head of the ring buffer, but does not
// remove that value.
// Requires that the ring buffer is not empty!
char ring_buffer_peek(struct RingBuffer *ring_buffer);

// Returns the value at the head of the ring buffer, and removes that
// value.
// Requires the ring buffer is not empty!
char ring_buffer_pop(struct RingBuffer *ring_buffer);

#endif  // ASBESTOS_LIB_RINGBUFFER_H_
