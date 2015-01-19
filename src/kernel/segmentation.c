#include <stdbool.h>
#include <x86.h>
#include "segmentation.h"

static struct SegmentDescriptor gdt[GDT_SIZE];

// Make a segment that spans the whole 32-bit address space.
struct SegmentDescriptor spanning_gdt_entry(
    bool writable, bool executable) {
  struct SegmentDescriptor result = {
      .limit_15_0 = 0xffff,
      .writable = writable,
      .executable = executable,
      .present = true,
      .limit_19_16 = 0xf,
      .granularity = true  // Multiply limit by 4KB.
  };
  return result;
}

void initialize_gdt() {
  // Start with the null segment.
  gdt[GDT_NULL_SEGMENT_OFFSET] = (struct SegmentDescriptor) {0};

  // Add a code segment.
  gdt[GDT_CODE_SEGMENT_OFFSET] = spanning_gdt_entry(false, true);

  // Add a data segment.
  gdt[GDT_DATA_SEGMENT_OFFSET] = spanning_gdt_entry(true, false);

  // TODO(jasonpr): Actually load the GDT!
}

void initialize_selectors() {
  struct SegmentSelector null_selector = {
    .index = GDT_NULL_SEGMENT_OFFSET
  };

  struct SegmentSelector code_selector = {
    .index = GDT_CODE_SEGMENT_OFFSET
  };

  struct SegmentSelector data_selector = {
    .index = GDT_DATA_SEGMENT_OFFSET
  };

  load_cs(code_selector);

  // Load DS for normal data access, SS for stack access, and ES for
  // string-related data access.
  load_ds(data_selector);
  load_ss(data_selector);
  load_es(data_selector);

  // We don't use the general-purpose segments.  Make sure we segfault
  // if we accidentally use them.
  load_fs(null_selector);
  load_gs(null_selector);
}

void segmentation_initialize() {
  initialize_gdt();
  initialize_selectors();
}
