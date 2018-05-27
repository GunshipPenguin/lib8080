#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_cmp);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(cmp_b) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_c) {
  i8080_write_byte(cpu, 0, 0xB9); // CMP C
  cpu->C = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_d) {
  i8080_write_byte(cpu, 0, 0xBA); // CMP D
  cpu->D = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_e) {
  i8080_write_byte(cpu, 0, 0xBB); // CMP E
  cpu->E = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_h) {
  i8080_write_byte(cpu, 0, 0xBC); // CMP H
  cpu->H = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_l) {
  i8080_write_byte(cpu, 0, 0xBD); // CMP L
  cpu->L = 1; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmp_m) {
  i8080_write_byte(cpu, 0, 0xBE); // CMP E
  i8080_write_byte(cpu, 0x05, 1);
  cpu->H = 0x00; cpu->L = 0x05; cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(cmp_a) {
  i8080_write_byte(cpu, 0, 0xBF); // CMP A
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// Bit flag tests
TEST_CASE(cmp_less) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x0A; cpu->B = 0x05;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cmp_greater) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x02; cpu->B = 0x0A;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cmp_not_equal) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0xFF; cpu->B = 0x0A;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(cmp_equal) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x0A; cpu->B = 0x0A;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(cmp_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(cmp_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0x04;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(cmp_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x00; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

// Comparisons with 0 are tricky
// https://retrocomputing.stackexchange.com/questions/6407/intel-8080-behaviour-of-the-carry-bit-when-comparing-a-value-with-0
TEST_CASE(cmp_compare_with_0) {
  i8080_write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x01; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}