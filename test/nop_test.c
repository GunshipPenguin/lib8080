#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_inr);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }
  reset_cpu();

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write8(i, 0);
  }

  cpu->PC = 0;
}
AFTER_EACH() {}

TEST_CASE(nop_0x00) {
  write8(0, 0x00);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x08) {
  write8(0, 0x08);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x10) {
  write8(0, 0x10);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x18) {
  write8(0, 0x18);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x20) {
  write8(0, 0x20);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x28) {
  write8(0, 0x28);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x30) {
  write8(0, 0x00);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x38) {
  write8(0, 0x38);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}