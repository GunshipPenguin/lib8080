#include "memory.h"
#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  create_memory(65536); // 64 KiB
  create_cpu();
  reset_cpu();

//  if((dbgfile = fopen("altair_out.txt", "w")) == NULL) {
//    perror("fopen");
//    exit(1);
//  }
//
//  if (dup2(fileno(dbgfile), fileno(stderr)) == -1) {
//    perror("dup2");
//    exit(1);
//  }

  cpu->PC = 0x100;

  load_memory("/home/rhys/CLionProjects/i8080/TEST.COM", 0x100);
  write_byte(5, 0xC9); // Inject RET at 0x05 to mock CP/M BDOS calls

  char buf[20000];
  buf[0] = '\0';

  while (1) {
    step_cpu();

    // CP/M warm boot (test finished and restarted itself)
    if (cpu->PC == 0) {
      return 0;
    }

    if (cpu->PC == 0x0005) {
      if (cpu->C == 2) { // Output char
        if (cpu->E != 0) {
          char val = cpu->E;
          putchar(val);
//          strcat(buf, &val);
          fflush(stdout);
        }
      } else if (cpu->C == 9) { // Output string
        for (int addr = CONCAT(cpu->D, cpu->E);read_byte(addr) != '$';addr++) {
          if (read_byte(addr) != 0) {
            char val = read_byte(addr);
            putchar(val);
//            strcat(buf, &val);
            fflush(stdout);
          }
        }
      }
    }
  }

  return 0;
}