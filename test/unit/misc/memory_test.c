#include <stdlib.h>
#include "i8080.h"
#include "attounit.h"

struct i8080 *cpu;

TEST_SUITE(memory)
BEFORE_EACH() {
  cpu = malloc(sizeof(struct i8080));
  cpu->memsize = 128;
  cpu->memory = malloc(sizeof(char) * 128);

  for (int addr=0;addr<cpu->memsize;addr++) {
    cpu->memory[addr] = '\0';
  }
}
AFTER_EACH() {
  free(cpu->memory);
  free(cpu);
}

TEST_CASE(read_beyond_end_return_0) {
  write_byte(cpu, 128, 0xFF);

  ASSERT_EQUAL(read_byte(cpu, 128), 0);
}
