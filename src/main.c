#include "memory.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
  create_memory(65536); // 64 KiB
  create_cpu();
  reset_cpu();

  cpu->PC = 0x100;
  write_byte(5, 0xC9);

  load_memory("/home/rhys/CLionProjects/altair/CPUTEST.COM", 0x100);

  while (1) {
    step_cpu();
  }

  return 0;
}