#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_ldax);
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
    write8(i, 0);
  }
}
AFTER_EACH() {}

TEST_CASE(ldax_b) {
  write8(0, 0x0A); // LDAX B
  write8(5, 0x01);
  cpu->A = 0x00; cpu->B = 0x00; cpu->C = 0x05;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
}


TEST_CASE(ldax_d) {
  write8(0, 0x1A); // LDAX D
  write8(5, 0x01);
  cpu->A = 0x00; cpu->D = 0x00; cpu->E = 0x05;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
}