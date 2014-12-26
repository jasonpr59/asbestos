#include "ringbuffer.h"

size_t ring_buffer_population(struct RingBuffer *ring_buffer) {
  return (ring_buffer->tail - ring_buffer->head) % ring_buffer->size;
}

bool ring_buffer_full(struct RingBuffer *ring_buffer) {
  return ring_buffer_population(ring_buffer) == ring_buffer->size - 1;
}

bool ring_buffer_empty(struct RingBuffer *ring_buffer) {
  return ring_buffer_population(ring_buffer) == 0;
}

int ring_buffer_append(struct RingBuffer *ring_buffer, char value) {
  if (ring_buffer_full(ring_buffer)) {
    return -1;
  }
  ring_buffer->buffer[ring_buffer->tail++] = value;
  ring_buffer->tail %= ring_buffer->size;
  return 0;
}

char ring_buffer_peek(struct RingBuffer *ring_buffer) {
  return ring_buffer->buffer[ring_buffer->head];
}

char ring_buffer_pop(struct RingBuffer *ring_buffer) {
  char result = ring_buffer_peek(ring_buffer);
  ring_buffer->head++;
  ring_buffer->head %= ring_buffer->size;
  return result;
}
