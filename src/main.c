#include "memory.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
  create_memory(4096);
  create_cpu();

  load_memory("/home/rhys/CLionProjects/altair/test.com");

  while (1) {
    step_cpu();
  }

  return 0;
}