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
  i8080_write_byte(cpu, 0, 0x90);
  cpu->B = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_c) {
  i8080_write_byte(cpu, 0, 0x91);
  cpu->C = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_d) {
  i8080_write_byte(cpu, 0, 0x92);
  cpu->D = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_e) {
  i8080_write_byte(cpu, 0, 0x93);
  cpu->E = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_h) {
  i8080_write_byte(cpu, 0, 0x94);
  cpu->H = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_l) {
  i8080_write_byte(cpu, 0, 0x95);
  cpu->L = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(sub_m) {
  i8080_write_byte(cpu, 0, 0x96);
  i8080_write_byte(cpu, 8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(sub_a) {
  i8080_write_byte(cpu, 0, 0x97);
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// i8080_flag bit tests
TEST_CASE(sub_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0x90); // ADD B
  cpu->A = 0x01; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(sub_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x04; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(sub_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0xFF; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(sub_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x1; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(sub_sets_a_flag_subtrahend_0) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x1; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(sub_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x01; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(sub_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0x90); // SUB B
  cpu->A = 0x00; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}
