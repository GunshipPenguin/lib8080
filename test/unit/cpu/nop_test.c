#include "unit/attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_nop);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(nop_0x00) {
  write_byte(0, 0x00);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x08) {
  write_byte(0, 0x08);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x10) {
  write_byte(0, 0x10);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x18) {
  write_byte(0, 0x18);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x20) {
  write_byte(0, 0x20);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x28) {
  write_byte(0, 0x28);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x30) {
  write_byte(0, 0x00);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(nop_0x38) {
  write_byte(0, 0x38);
  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}