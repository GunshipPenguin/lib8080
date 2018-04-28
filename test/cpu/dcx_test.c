#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_dcx);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(dcx_b) {
  write_byte(0, 0x0B); // DCX B
  cpu->B = 0x01; cpu->C = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->B, 0x00);
  ASSERT_EQUAL(cpu->C, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcx_d) {
  write_byte(0, 0x1B); // DCX D
  cpu->D = 0x01; cpu->E = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 0x00);
  ASSERT_EQUAL(cpu->E, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcx_h) {
  write_byte(0, 0x2B); // DCX H
  cpu->H = 0x01; cpu->L = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->H, 0x00);
  ASSERT_EQUAL(cpu->L, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcx_sp) {
  write_byte(0, 0x3B); // DCX SP
  cpu->SP = 0x01;

  step_cpu();

  ASSERT_EQUAL(cpu->SP, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}
