#include <stdbool.h>
#include <segments.h>
#include <x86.h>
#include "segmentation.h"

static struct SegmentDescriptor gdt[GDT_SIZE];
static struct PseudoDescriptor gdt_descriptor = {
  .limit = sizeof(struct SegmentDescriptor) * GDT_SIZE - 1,
  .base = (uintptr_t) &gdt
};

// Make a segment that spans the whole 32-bit address space.
struct SegmentDescriptor spanning_gdt_entry(
    bool writable, bool executable) {
  struct SegmentDescriptor result = {
      .limit_15_0 = 0xffff,
      .writable = writable,
      .executable = executable,
      .non_system = true,
      .present = true,
      .limit_19_16 = 0xf,
      .default_size_32 = true,
      .granularity_4k = true
  };
  return result;
}

void initialize_gdt() {
  // Start with the null segment.
  gdt[GDT_NULL_SEGMENT_OFFSET] = (struct SegmentDescriptor) {0};

  // Add a code segment.
  // I can't find documentation that the code segment must be
  // writeable.  But, it's the only way I can avoid a GP fault, and
  // GRUB makes a writeable code segment, too.  So, it's probably
  // okay!
  gdt[GDT_CODE_SEGMENT_OFFSET] = spanning_gdt_entry(true, true);

  // Add a data segment.
  gdt[GDT_DATA_SEGMENT_OFFSET] = spanning_gdt_entry(true, false);

  load_gdt(&gdt_descriptor);
}

void initialize_selectors() {
  load_cs(GDT_CODE_SELECTOR);

  // Load DS for normal data access, SS for stack access, and ES for
  // string-related data access.
  load_ds(GDT_DATA_SELECTOR);
  load_ss(GDT_DATA_SELECTOR);
  load_es(GDT_DATA_SELECTOR);

  // We don't use the general-purpose segments.  Make sure we segfault
  // if we accidentally use them.
  load_fs(GDT_NULL_SELECTOR);
  load_gs(GDT_NULL_SELECTOR);
}

void segmentation_initialize() {
  initialize_gdt();
  initialize_selectors();
}
