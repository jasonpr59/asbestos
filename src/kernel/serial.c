// This file implements serial communication via a UART like the 8250
// or 16550.

// Some good resources include:
// http://pdf1.alldatasheet.com/datasheet-pdf/view/89961/NSC/INS8250/+5J873UKPC/1pOuCtzB+/datasheet.pdf
// www.ti.com/lit/ds/symlink/pc16550d.pdf
// www.sci.muni.cz/docs/pc/serport.txt
// wiki.osdev.org/Serial_Ports


#include <stdbool.h>
#include <x86.h>
#include "input.h"
#include "serial.h"

#define COM1_IO_PORT 0x3f8

// The next two constants are valid when DLAB = 0.
#define UART_DATA_IO_PORT (COM1_IO_PORT + 0)
#define UART_INTERRUPT_ENABLE_IO_PORT (COM1_IO_PORT + 1)

// The next two constants valid when DLAB = 1.
#define UART_BAUD_DIVISOR_LSB_IO_PORT (COM1_IO_PORT + 0)
#define UART_BAUD_DIVISOR_MSB_IO_PORT (COM1_IO_PORT + 1)

// The remaining constants are always valid, no matter the value of
// DLAB.
// Note that FIFO_CONTROL and INTERRUPT_IDENTIFIER are the same port.
// FIFO_CONTROL is write-only; INTERRUPT_IDENTIFIER is read-only.

#define UART_FIFO_CONTROL_IO_PORT (COM1_IO_PORT + 2)
#define UART_INTERRUPT_IDENTIFIER_IO_PORT (COM1_IO_PORT + 2)
#define UART_LINE_CONTROL_IO_PORT (COM1_IO_PORT + 3)
#define UART_MODEM_CONTROL_IO_PORT (COM1_IO_PORT + 4)
#define UART_LINE_STATUS_IO_PORT (COM1_IO_PORT + 5)
#define UART_MODEM_STATUS_IO_PORT (COM1_IO_PORT + 6)
#define UART_SCRATCH_IO_PORT (COM1_IO_PORT + 7)

#define UART_INTERRUPT_DATA_AVAILABLE 0x1
#define UART_INTERRUPT_TX_EMPTY 0x2
#define UART_INTERRUPT_RX_LINE_STATUS 0x4
#define UART_INTERRUPT_MODEM_STATUS 0x8


#define UART_INTERRUPT_PENDING 0x1
#define UART_INTERRUPT_ID_BITS 0x6

#define UART_LINE_CONTROL_WORD_LENGTH_BITS 0x3
#define UART_LINE_CONTROL_WORD_LENGTH_5 0x0
#define UART_LINE_CONTROL_WORD_LENGTH_6 0x1
#define UART_LINE_CONTROL_WORD_LENGTH_7 0x2
#define UART_LINE_CONTROL_WORD_LENGTH_8 0x3

#define UART_LINE_CONTROL_EXTRA_STOP_BIT 0x4
#define UART_LINE_CONTROL_PARITY_ENABLE 0x8
#define UART_LINE_CONTROL_EVEN_PARITY 0x10
#define UART_LINE_CONTROL_STICK_PARITY 0x20
#define UART_LINE_CONTROL_SET_BREAK 0x40
#define UART_LINE_CONTROL_DLAB 0x80

#define UART_LINE_STATUS_DATA_READY 0x1
#define UART_LINE_STATUS_OVERRUN_ERROR 0x2
#define UART_LINE_STATUS_PARITY_ERROR 0x4
#define UART_LINE_STATUS_FRAMING_ERROR 0x8
#define UART_LINE_STATUS_BREAK_INTERRUPT 0x10
#define UART_LINE_STATUS_TX_HOLDING_REG_EMPTY 0x20
#define UART_LINE_STATUS_TX_EMPTY 0x40

bool serial_can_transmit() {
  return inb(UART_LINE_STATUS_IO_PORT) & 
      UART_LINE_STATUS_TX_HOLDING_REG_EMPTY;
}

void serial_write(char character) {
  while (!serial_can_transmit()) {
    // Spin around.
  }
  outb(UART_DATA_IO_PORT, character);
}

bool serial_can_read() {
  return inb(UART_LINE_STATUS_IO_PORT) &
    UART_LINE_STATUS_DATA_READY;
}

int serial_read(char *output) {
  if (!serial_can_read()) {
    return INPUT_EXHAUSTED;
  }
  *output = inb(UART_DATA_IO_PORT);
  return 0;
}

void serial_initialize() {
  // Set baud rate to highest possible value.  Requires setting the
  // divisor latch (DLAB).
  outb(UART_LINE_CONTROL_IO_PORT, UART_LINE_CONTROL_DLAB);
  outb(UART_BAUD_DIVISOR_LSB_IO_PORT, 1);
  outb(UART_BAUD_DIVISOR_MSB_IO_PORT, 0);

  // Unset the divisor latch, simultaneously setting up 8N1 communication.
  outb(UART_LINE_CONTROL_IO_PORT, UART_LINE_CONTROL_WORD_LENGTH_8);

  // Fire an interrupt when a new byte is received.
  outb(UART_INTERRUPT_ENABLE_IO_PORT, UART_INTERRUPT_DATA_AVAILABLE);
}
