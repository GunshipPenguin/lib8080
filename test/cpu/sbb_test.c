#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sbb)
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(sbb_b) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 0xFF; cpu->B = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_c) {
  write_byte(0, 0x99); // SBB C
  cpu->A = 0xFF; cpu->C = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_d) {
  write_byte(0, 0x9A); // SBB D
  cpu->A = 0xFF; cpu->D = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_e) {
  write_byte(0, 0x9B); // SBB E
  cpu->A = 0xFF; cpu->E = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_h) {
  write_byte(0, 0x9C); // SBB H
  cpu->A = 0xFF; cpu->H = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_l) {
  write_byte(0, 0x9D); // SBB L
  cpu->A = 0xFF; cpu->L = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_m) {
  write_byte(0, 0x9E); // SBB M
  write_byte(10, 0xFF);
  cpu->A = 0xFF; cpu->H = 0x00; cpu->L = 0xA;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(sbb_a) {
  write_byte(0, 0x9F); // SBB A
  cpu->A = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(FLAG_C));
}

// Bit flag tests
TEST_CASE(sbb_unsets_c_flag) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 1; cpu->B = 1;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_FALSE(get_flag(FLAG_Z));
}

TEST_CASE(sbb_sets_a_flag) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 0x10; cpu->B = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_A));
}

TEST_CASE(sbb_sets_z_flag) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 1; cpu->B = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
}

TEST_CASE(sbb_sets_p_flag) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 4; cpu->B = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_P));
}

TEST_CASE(sbb_sets_s_flag) {
  write_byte(0, 0x98); // SBB B
  cpu->A = 0xFF; cpu->B = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_S));
}
