#include <segments.h>
#include <stdint.h>

uintptr_t pseudo_descriptor_address(struct PseudoDescriptor *pd) {
  // The first two bytes are padding.
  return ((uintptr_t) pd) + 2;
}
