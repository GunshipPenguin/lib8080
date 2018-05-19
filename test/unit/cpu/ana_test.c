#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_ana);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(ana_b) {
  write_byte(cpu, 0, 0xA0);
  cpu->B = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_c) {
  write_byte(cpu, 0, 0xA1);
  cpu->C = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_d) {
  write_byte(cpu, 0, 0xA2);
  cpu->D = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_e) {
  write_byte(cpu, 0, 0xA3);
  cpu->E = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_h) {
  write_byte(cpu, 0, 0xA4);
  cpu->H = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_l) {
  write_byte(cpu, 0, 0xA5);
  cpu->L = 6; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_m) {
  write_byte(cpu, 0, 0xA6);
  write_byte(cpu, 8, 6);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_a) {
  write_byte(cpu, 0, 0xA7);
  cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 10);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Flag bit tests
TEST_CASE(ana_resets_c_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xF0; cpu->B = 0x00;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(ana_sets_z_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xFF; cpu->B = 0x00;
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(ana_sets_s_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xFF; cpu->B = 0xFF;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(ana_sets_p_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0x07; cpu->B = 0x03;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

// On the 8080, logical and instructions set the aux carry flag to the logical
// or of bit 3 of the values involved in the operation
TEST_CASE(ana_sets_a_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0x08; cpu->B = 0xF0;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(ana_resets_a_flag) {
  write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xF0; cpu->B = 0x07;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_A));
}
