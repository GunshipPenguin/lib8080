#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu/cpu_test_helpers.h"

TEST_SUITE(instruction_inr);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(inr_b) {
  write_byte(0, 0x04);
  cpu->B = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->B, 1);
}


TEST_CASE(inr_c) {
  write_byte(0, 0x0C);
  cpu->C = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_d) {
  write_byte(0, 0x14);
  cpu->B = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_e) {
  write_byte(0, 0x1C);
  cpu->C = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_h) {
  write_byte(0, 0x24);
  cpu->H = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_l) {
  write_byte(0, 0x2C);
  cpu->L = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_m) {
  write_byte(0, 0x34);
  write_byte(0x08, 0);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read_byte(CONCAT(cpu->H, cpu->L)), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_a) {
  write_byte(0, 0x3C);
  cpu->A = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Flag bit tests
TEST_CASE(inr_sets_z_flag) {
  write_byte(0, 0x3C); // INR A
  cpu->A = 0xFF;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
}

TEST_CASE(inr_sets_p_flag) {
  write_byte(0, 0x3C); // INR A
  cpu->A = 0x02;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_P));
}

TEST_CASE(inr_sets_s_flag) {
  write_byte(0, 0x3C); // INR A
  cpu->A = 0x7F;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_S));
}

TEST_CASE(inr_sets_a_flag) {
  write_byte(0, 0x3C); // INR A
  cpu->A = 0x0F;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_A));
}