#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_cma);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }

  reset_cpu();
  cpu->PC = 0;

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write_byte(i, 0);
  }
}
AFTER_EACH() {}

TEST_CASE(cma) {
  write_byte(0, 0x2F); // CMA
  cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}
