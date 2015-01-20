#ifndef ASBESTOS_LIB_SEGMENTS_H_
#define ASBESTOS_LIB_SEGMENTS_H_

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

#endif  // ASBESTOS_LIB_SEGMENTS_H_
