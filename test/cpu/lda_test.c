#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_lda);
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

TEST_CASE(lda) {
  write8(0, 0x3A); // LDA
  write16(1, 5); // a16
  write8(5, 1);
  cpu->A = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
}