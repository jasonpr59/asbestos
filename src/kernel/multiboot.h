#ifndef ASBESTOS_KERNEL_MULTIBOOT_H_
#define ASBESTOS_KERNEL_MULTIBOOT_H_

// The names in this file are chosen to conform to those in GNU
// multiboot documentation at
// http://www.gnu.org/software/grub/manual/multiboot/multiboot.html

#define MULTIBOOT_HANDOFF_EAX 0x2BADB002

#define MEM_FLAG (1 << 0)
#define BOOT_DEVICE_FLAG (1 << 1)
#define CMDLINE_FLAG (1 << 2)
#define MODS_FLAG (1 << 3)
#define SYMS_LOW_FLAG (1 << 4)
#define SYMS_HIGH_FLAG (1 << 5)
#define MMAP_FLAG (1 << 6)
#define DRIVES_FLAG (1 << 7)
#define CONFIG_TABLE_FLAG (1 << 8)
#define BOOT_LOADER_NAME_FLAG (1 << 9)
#define APM_TABLEFLAG (1 << 10)
#define VBE_FLAG (1 << 11)


struct MultibootInfo {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  uint32_t syms_1;
  uint32_t syms_2;
  uint32_t syms_3;
  uint32_t syms_4;
  uint32_t mmap_length;
  uint32_t mmap_addr;
  uint32_t drives_length;
  uint32_t drives_addr;
  uint32_t config_table;
  uint32_t boot_loader_name;
  uint32_t apm_table;
  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint16_t vbe_mode;
  uint16_t vbe_interface_seg;
  uint16_t vbe_interface_off;
  uint16_t vbe_interface_len;
};

#define MULTIBOOT_MEMORY_USABLE 1

struct MultibootMemoryMapEntry {
  uint32_t size;
  uint64_t base_addr;
  uint64_t length;
  uint32_t type;
} __attribute__((packed));

#endif  // ASBESTOS_KERNEL_MULTIBOOT_H_
