#include <x86.h>
#include "cprintf.h"
#include "link_address.h"
#include "memory_catalog.h"
#include "monitor.h"
#include "multiboot.h"
#include "panic.h"
#include "keyboard.h"
#include "segmentation.h"
#include "serial.h"
#include "vga.h"

void kernel_initialize_terminal() {
  serial_initialize();
  vga_initialize();
  keyboard_initialize();
}

void kernel_validate_multiboot_handoff(uint32_t handoff_eax,
				       struct MultibootInfo *multiboot_info) {
  if (handoff_eax != MULTIBOOT_HANDOFF_EAX) {
    panic("[MULTIBOOT] Bad handoff %%eax value: 0x%08x.\n",handoff_eax);
  }

  if (!(multiboot_info->flags & MEM_FLAG)) {
    panic("[MULTIBOOT] Multiboot info `mem` flag not set.\n");
  }

  if (!(multiboot_info->flags & MMAP_FLAG)) {
    panic("[MULTIBOOT] Multiboot info `mmap` flag not set.\n");
  }

  cprintf("Multiboot handoff completed successfully.\n");
}

void kernel_main(struct PushedRegisters registers) {
  kernel_initialize_terminal();
  cprintf("Starting up Asbestos.\n");

  cprintf("Updating segmentation scheme.\n")
  segmentation_initialize();

  struct MultibootInfo *multiboot_info = (struct MultibootInfo *) registers.ebx;
  kernel_validate_multiboot_handoff(registers.eax, multiboot_info);
  memory_catalog_initialize(multiboot_info);

  run_monitor();
}
