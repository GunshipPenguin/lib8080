#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_ora);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(ora_b) {
  i8080_write_byte(cpu, 0, 0xB0);
  cpu->B = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_c) {
  i8080_write_byte(cpu, 0, 0xB1);
  cpu->C = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_d) {
  i8080_write_byte(cpu, 0, 0xB2);
  cpu->D = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_e) {
  i8080_write_byte(cpu, 0, 0xB3);
  cpu->E = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_h) {
  i8080_write_byte(cpu, 0, 0xB4);
  cpu->H = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_l) {
  i8080_write_byte(cpu, 0, 0xB5);
  cpu->L = 6; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ora_m) {
  i8080_write_byte(cpu, 0, 0xB6);
  i8080_write_byte(cpu, 8, 6);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(ora_a) {
  i8080_write_byte(cpu, 0, 0xB7);
  cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 10);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// i8080_flag bit tests
TEST_CASE(ora_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xB0); // ORA B
  cpu->A = 0xF0; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(ora_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xB0); // ORA B
  cpu->A = 0x00; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(ora_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xB0); // ORA B
  cpu->A = 0x00; cpu->B = 0xFF;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(ora_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xB0); // ORA B
  cpu->A = 0x00; cpu->B = 0x03;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}