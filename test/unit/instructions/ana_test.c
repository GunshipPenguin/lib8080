#include "attounit.h"
#include "i8080.h"
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
  i8080_write_byte(cpu, 0, 0xA0);
  cpu->B = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_c) {
  i8080_write_byte(cpu, 0, 0xA1);
  cpu->C = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_d) {
  i8080_write_byte(cpu, 0, 0xA2);
  cpu->D = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_e) {
  i8080_write_byte(cpu, 0, 0xA3);
  cpu->E = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_h) {
  i8080_write_byte(cpu, 0, 0xA4);
  cpu->H = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_l) {
  i8080_write_byte(cpu, 0, 0xA5);
  cpu->L = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ana_m) {
  i8080_write_byte(cpu, 0, 0xA6);
  i8080_write_byte(cpu, 8, 6);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(ana_a) {
  i8080_write_byte(cpu, 0, 0xA7);
  cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 10);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// i8080_flag bit tests
TEST_CASE(ana_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xF0; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(ana_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xFF; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(ana_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xFF; cpu->B = 0xFF;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(ana_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0x07; cpu->B = 0x03;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

// On the 8080, logical and instructions set the aux carry flag to the logical
// or of bit 3 of the values involved in the operation
TEST_CASE(ana_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0x08; cpu->B = 0xF0;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(ana_resets_a_flag) {
  i8080_write_byte(cpu, 0, 0xA0); // ANA B
  cpu->A = 0xF0; cpu->B = 0x07;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_A));
}
