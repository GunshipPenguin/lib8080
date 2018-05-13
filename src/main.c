#include "memory.h"
#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  struct i8080 *cpu = create_cpu();
  reset_cpu(cpu);

  return 0;
}