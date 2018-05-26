#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sub);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(sub_b) {
  write_byte(cpu, 0, 0x90);
  cpu->B = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_c) {
  write_byte(cpu, 0, 0x91);
  cpu->C = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_d) {
  write_byte(cpu, 0, 0x92);
  cpu->D = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_e) {
  write_byte(cpu, 0, 0x93);
  cpu->E = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_h) {
  write_byte(cpu, 0, 0x94);
  cpu->H = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_l) {
  write_byte(cpu, 0, 0x95);
  cpu->L = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_m) {
  write_byte(cpu, 0, 0x96);
  write_byte(cpu, 8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(sub_a) {
  write_byte(cpu, 0, 0x97);
  cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// Flag bit tests
TEST_CASE(sub_sets_z_flag) {
  write_byte(cpu, 0, 0x90); // ADD B
  cpu->A = 0x01; cpu->B = 0x01;
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(sub_sets_p_flag) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x04; cpu->B = 0x01;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(sub_sets_s_flag) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0xFF; cpu->B = 0x01;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(sub_sets_a_flag) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x1; cpu->B = 0x01;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sub_sets_a_flag_subtrahend_0) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x1; cpu->B = 0x00;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sub_resets_c_flag) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x01; cpu->B = 0x01;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sub_sets_c_flag) {
  write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x00; cpu->B = 0x01;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}
