#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_xchg);
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

TEST_CASE(xchg) {
  write_byte(0, 0xEB); // XCHG
  cpu->H = 1; cpu->L = 2;
  cpu->D = 3; cpu->E = 4;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->E, 2);
  ASSERT_EQUAL(cpu->H, 3);
  ASSERT_EQUAL(cpu->L, 4);
}