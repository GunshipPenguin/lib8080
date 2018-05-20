#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sbb)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(sbb_b) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 0xF0; cpu->B = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_c) {
  write_byte(cpu, 0, 0x99); // SBB C
  cpu->A = 0xF0; cpu->C = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_d) {
  write_byte(cpu, 0, 0x9A); // SBB D
  cpu->A = 0xF0; cpu->D = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_e) {
  write_byte(cpu, 0, 0x9B); // SBB E
  cpu->A = 0xF0; cpu->E = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_h) {
  write_byte(cpu, 0, 0x9C); // SBB H
  cpu->A = 0xF0; cpu->H = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_l) {
  write_byte(cpu, 0, 0x9D); // SBB L
  cpu->A = 0xF0; cpu->L = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_m) {
  write_byte(cpu, 0, 0x9E); // SBB M
  write_byte(cpu, 10, 0x0F);
  cpu->A = 0xF0; cpu->H = 0x00; cpu->L = 0xA;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_a) {
  write_byte(cpu, 0, 0x9F); // SBB A
  cpu->A = 0xF0;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

// Bit flag tests
TEST_CASE(sbb_resets_c_flag) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 0xF0; cpu->B = 0x0F;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbb_sets_a_flag) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 0x01; cpu->B = 0;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sbb_sets_z_flag) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 1; cpu->B = 0;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(sbb_sets_p_flag) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 4; cpu->B = 1;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(sbb_sets_s_flag) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 0xFF; cpu->B = 1;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

/*
 * This is a finicky corner case since a naive implementation would do this
 * by adding 1 to 0xFF, resulting in 0 (since B is an 8 bit register)
 * and then subtracting 0 from the contents of the A register, thus leaving A
 * unchanged.
 */
TEST_CASE(sbb_subtrahend_0xFF_with_borrow) {
  write_byte(cpu, 0, 0x98); // SBB B
  cpu->A = 0xAB; cpu->B = 0xFF;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xAB);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_FALSE(get_flag(cpu, FLAG_A));
}
