#include "monitor.h"
#include "cprintf.h"
#include "input.h"

#define PROMPT_SIZE 100

void run_monitor() {
  cprintf("Started the Asbestos Kernel Monitor.\n");
  cprintf("Currently, this is just an echo prompt.\n");

  char prompt[PROMPT_SIZE];
  while (1) {
    cprintf("$ ");
    input_string(prompt, PROMPT_SIZE);
    cprintf(prompt);
  }
}
