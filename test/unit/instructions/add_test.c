#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_add);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}


// Individual opcode tests
TEST_CASE(add_b) {
  i8080_write_byte(cpu, 0, 0x80);
  cpu->B = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(add_c) {
  i8080_write_byte(cpu, 0, 0x81);
  cpu->C = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(add_d) {
  i8080_write_byte(cpu, 0, 0x82);
  cpu->D = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(add_e) {
  i8080_write_byte(cpu, 0, 0x83);
  cpu->E = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(add_h) {
  i8080_write_byte(cpu, 0, 0x84);
  cpu->H = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_l) {
  i8080_write_byte(cpu, 0, 0x85);
  cpu->L = 1; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(add_m) {
  i8080_write_byte(cpu, 0, 0x86);
  i8080_write_byte(cpu, 8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(add_a) {
  i8080_write_byte(cpu, 0, 0x87);
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// i8080_flag bit tests
TEST_CASE(add_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADD B
  cpu->A = 0x00; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(add_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADD B
  cpu->A = 0x02; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(add_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADD B
  cpu->A = 0x7F; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(add_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADD B
  cpu->A = 0x0F; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(add_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADD B
  cpu->A = 0xFF; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}