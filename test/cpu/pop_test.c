#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_pop);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(pop_b) {
  write_byte(0, 0xC1); // POP B
  cpu->B = 0x00; cpu->C = 0x00;
  push_stackw(0xABCD);

  step_cpu();

  ASSERT_EQUAL(cpu->B, 0xAB);
  ASSERT_EQUAL(cpu->C, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(pop_d) {
  write_byte(0, 0xD1); // POP D
  cpu->D = 0x00; cpu->E = 0x00;
  push_stackw(0xABCD);

  step_cpu();

  ASSERT_EQUAL(cpu->D, 0xAB);
  ASSERT_EQUAL(cpu->E, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(pop_h) {
  write_byte(0, 0xE1); // POP H
  cpu->H = 0x00; cpu->L = 0x00;
  push_stackw(0xABCD);

  step_cpu();

  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(pop_psw) {
  write_byte(0, 0xF1); // POP PSW
  cpu->A = 0x00; cpu->flags = 2;
  push_stackw(0xD7AB);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xAB);
  ASSERT_TRUE(get_flag(FLAG_C));
  ASSERT_TRUE(get_flag(FLAG_P));
  ASSERT_TRUE(get_flag(FLAG_A));
  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_TRUE(get_flag(FLAG_S));
  ASSERT_EQUAL(cpu->PC, 1);
}
