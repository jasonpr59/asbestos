#include "vga.h"

// Returns a color palette byte that specifies a foreground and
// background color for a character on a VGA display.
uint8_t vga_color_palette_byte(enum VgaColors foreground, enum VgaColors background) {
  return foreground | background << 4;
}

// Returns a 16-bit value that can be sent to a VGA display to specify
// a character and a color palette.
VgaCharacter vga_character(char character, uint8_t color_palette) {
  return (((uint16_t) color_palette) << 8) | ((uint16_t) character);
}

static const size_t kVgaWidth = 80;
static const size_t kVgaHeight = 25;

// The VGA buffer is memory-mapped to 0xB8000.
static const uint32_t kVgaBuffer = 0xB8000;

// Globals for controling the hardware terminal.
size_t vga_row;
size_t vga_column;
uint8_t vga_color_palette;
VgaCharacter *vga_buffer;

void vga_initialize() {
  vga_row = 0;
  vga_column = 0;
  vga_color_palette = vga_color_palette_byte(kColorLightGray, kColorBlack);
  vga_buffer = (VgaCharacter *) kVgaBuffer;

  for (size_t entry = 0; entry < kVgaWidth * kVgaHeight; entry++) {
    vga_buffer[entry] = vga_character(' ', vga_color_palette);
  }
}

void vga_set_color_palette(uint8_t color_palette) {
  vga_color_palette = color_palette;
}

void vga_place_character(char character, uint8_t color_palette, int row, int column) {
  const int index = row * kVgaWidth + column;
  vga_buffer[index] = vga_character(character, color_palette);
}

// Reposition the cursor, and possibly scroll the screen, so that the
// cursor is in bounds.
void vga_reposition() {
  if (vga_column >= kVgaWidth) {
    vga_column = 0;
    vga_row++;
  }
  int overhang = vga_row - kVgaHeight + 1;
  if (overhang > 0) {
    // TODO(jasonpr): "Scroll the viewport."
    vga_row = kVgaHeight - 1;
  }

}

void vga_write_newline() {
  vga_column = 0;
  vga_row++;
  vga_reposition();
}

void vga_write(char character) {
  // Write the character.
  vga_place_character(character, vga_color_palette, vga_row, vga_column);
  // Advance the cursor.
  vga_column++;
  vga_reposition();
}

void vga_write_string(char* string) {
  char* next_char = string;
  while (*next_char != 0) {
    vga_write(*next_char++);
  }
}
