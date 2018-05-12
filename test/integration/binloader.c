#include "memory.h"
#include "cpu.h"
#include <stdio.h>

void intercept_bdos_call() {
  if (cpu->C == 2) { // BDOS function 2 (C_WRITE) - Console output
    if (cpu->E != 0) {
      putchar((char) cpu->E);
    }
  } else if (cpu->C == 9) { // BDOS function 9 (C_WRITESTR) - Output string
    for (int addr = CONCAT(cpu->D, cpu->E);read_byte(addr) != '$';addr++) {
      if (read_byte(addr) != 0) {
        putchar((char) read_byte(addr));
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: binloader <filename>\n");
    return 1;
  }

  create_memory(65536); // 64 KiB
  create_cpu();
  reset_cpu();

  cpu->PC = 0x100;

  // Load the binary as a CP/M program (loaded at offset 0x100)
  load_memory(argv[1], 0x100);

  // Inject RET at 0x05 to allow for mocking of CP/M BDOS system calls
  write_byte(5, 0xC9);

  while (1) {
    step_cpu();

    // CP/M warm boot (test finished and restarted itself)
    if (cpu->PC == 0) {
      return 0;
    }

    // CP/M BDOS call
    if (cpu->PC == 0x0005) {
      intercept_bdos_call();
    }
  }
}