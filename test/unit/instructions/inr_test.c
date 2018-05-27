#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_inr);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(inr_b) {
  i8080_write_byte(cpu, 0, 0x04);
  cpu->B = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->B, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(inr_c) {
  i8080_write_byte(cpu, 0, 0x0C);
  cpu->C = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inr_d) {
  i8080_write_byte(cpu, 0, 0x14);
  cpu->B = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(inr_e) {
  i8080_write_byte(cpu, 0, 0x1C);
  cpu->C = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inr_h) {
  i8080_write_byte(cpu, 0, 0x24);
  cpu->H = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(inr_l) {
  i8080_write_byte(cpu, 0, 0x2C);
  cpu->L = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inr_m) {
  i8080_write_byte(cpu, 0, 0x34);
  i8080_write_byte(cpu, 0x08, 0);
  cpu->H = 0; cpu->L = 0x08;

  i8080_step(cpu);
  ASSERT_EQUAL(i8080_read_byte(cpu, 0x08), 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(inr_a) {
  i8080_write_byte(cpu, 0, 0x3C);
  cpu->A = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

// i8080_flag bit tests
TEST_CASE(inr_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0x3C); // INR A
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(inr_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0x3C); // INR A
  cpu->A = 0x02;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(inr_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0x3C); // INR A
  cpu->A = 0x7F;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(inr_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0x3C); // INR A
  cpu->A = 0x0F;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}