#include <stddef.h>
#include <stdint.h>

#ifndef VGA_H_
#define VGA_H_

typedef uint16_t VgaCharacter;

enum VgaColors {
  kColorBlack = 0,
  kColorBlue = 1,
  kColorGreen = 2,
  kColorCyan = 3,
  kColorRed = 4,
  kColorMagenta = 5,
  kColorBrown = 6,
  kColorLightGray = 7,
  kColorDarkGray = 8,
  kColorLightBlue = 9,
  kColorLightGreen = 10,
  kColorLightCyan = 11,
  kColorLightRed = 12,
  kColorLightMagenta = 13,
  kColorLightBrown = 14,
  kColorWhite = 15,
};

uint8_t vga_color_palette_byte(enum VgaColors foreground, enum VgaColors background);
VgaCharacter vga_character(char character, uint8_t color_palette);
void vga_initialize();
void vga_set_color_palette(uint8_t color_palette);
void vga_place_character(char character, uint8_t color_palette, int row, int column);
void vga_write(char character);
void vga_write_newline();
void vga_write_string(char* string);

#endif  // VGA_H_
