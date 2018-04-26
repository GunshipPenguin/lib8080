#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_sphl);
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

TEST_CASE(sphl) {
  write_byte(0, 0xF9); // SPHL
  cpu->H = 0xAB; cpu->L = 0xCD;
  cpu->SP = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
}