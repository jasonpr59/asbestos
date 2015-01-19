#ifndef ASBESTOS_KERNEL_SEGMENT_H_
#define ASBESTOS_KERNEL_SEGMENT_H_

#include <stdint.h>

// Useful resources:
// http://www.intel.com/design/pentium/manuals/24143004.pdf
// https://css.csail.mit.edu/6.858/2010/readings/i386.pdf

struct SegmentDescriptor {
  // The low 15 bits of the segment limit.  Multiply by by 4KB if
  // granularity bit is set, or by 1 byte if granularity bit is
  // cleared.
  uint16_t limit_15_0;
  // The low 15 bits of the base address.
  uint16_t base_15_0;
  uint8_t base_23_16;
  // Set by the whenever it uses this segment.
  unsigned int accessed : 1;
  unsigned int writable : 1;
  // Pertains to variable-sized segments.  Clear it and forget it.
  unsigned int expand_down : 1;
  // If set, it's a code segment.  If cleared, it's a data segment.
  unsigned int executable : 1;
  // If set, it's an LDT entry.  If cleared, it's a GDT entry.
  unsigned int local : 1;
  // DPL.  System is 0, user is 3.
  unsigned int privilege_level : 2;
  unsigned int present : 1;
  unsigned int limit_19_16 : 4;
  // Available for our own use.
  unsigned int unused : 1;
  unsigned int reserved : 1;
  // If set, operations in this segment default to 32-bit operations.
  // If cleared, they default to 16-bit operations.
  unsigned int default_size : 1;
  // See the limit_* fields.
  unsigned int granularity : 1;
  uint8_t base_31_24;
} __attribute__((packed));

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

#endif  // ASBESTOS_KERNEL_SEGMENT_H_
