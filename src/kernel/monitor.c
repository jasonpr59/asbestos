#include "monitor.h"
#include "backtrace.h"
#include "cprintf.h"
#include "input.h"
#include "string.h"

#define PROMPT_SIZE 100

void run_monitor() {
  cprintf("Started the Asbestos Kernel Monitor.\n");
  cprintf("Commands: backtrace, version.\n");

  char prompt[PROMPT_SIZE];
  while (1) {
    cprintf("$ ");
    input_string(prompt, PROMPT_SIZE);
    if (!strcmp("version", prompt)) {
      cprintf("Asbestos v0.0 (no version numbers yet!)\n");
    } else if (!strcmp("backtrace", prompt)) {
      cprintf("Backtrace requested.\n");
      print_backtrace();
    } else {
      cprintf("Unknown command: %s", prompt);
    }
    cprintf("\n");
  }
}
