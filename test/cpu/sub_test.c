#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sub);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(sub_b) {
  write_byte(0, 0x90);
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_c) {
  write_byte(0, 0x91);
  cpu->C = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_d) {
  write_byte(0, 0x92);
  cpu->D = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_e) {
  write_byte(0, 0x93);
  cpu->E = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_h) {
  write_byte(0, 0x94);
  cpu->H = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_l) {
  write_byte(0, 0x95);
  cpu->L = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_m) {
  write_byte(0, 0x96);
  write_byte(8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_a) {
  write_byte(0, 0x97);
  cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Flag bit tests
TEST_CASE(sub_sets_z_flag) {
  write_byte(0, 0x90); // ADD B
  cpu->A = 0x01; cpu->B = 0x01;
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
}

TEST_CASE(sub_sets_p_flag) {
  write_byte(0, 0x90); // SUB B
  cpu->A = 0x04; cpu->B = 0x01;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_P));
}

TEST_CASE(sub_sets_s_flag) {
  write_byte(0, 0x90); // SUB B
  cpu->A = 0xFF; cpu->B = 0x01;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_S));
}

TEST_CASE(sub_sets_a_flag) {
  write_byte(0, 0x90); // SUB B
  cpu->A = 0x10; cpu->B = 0x01;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_A));
}

TEST_CASE(sub_sets_c_flag) {
  write_byte(0, 0x90); // SUB B
  cpu->A = 0x00; cpu->B = 0x01;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_C));
}