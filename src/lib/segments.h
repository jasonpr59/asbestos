#ifndef ASBESTOS_LIB_SEGMENTS_H_
#define ASBESTOS_LIB_SEGMENTS_H_

#include <stdint.h>

struct SegmentSelector {
  // What privileges the CPU must require to use this segment.
  // If the referenced descriptor has a stricter privilege level,
  // then that constraint will be enforced instead.
  unsigned int requested_privilege_level : 2;
  // Which table contains the segment. 0 = GDT, 1 = LDT.
  unsigned int local : 1;
  // The index into the descriptor table.
  unsigned int index : 13;
} __attribute__((packed));

struct PseudoDescriptor {
  uint16_t alignment_padding;
  uint16_t limit;
  uintptr_t base;
} __attribute__((aligned(4), packed));

uintptr_t pseudo_descriptor_address(struct PseudoDescriptor *pd);

#endif  // ASBESTOS_LIB_SEGMENTS_H_
