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
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_c) {
  write_byte(cpu, 0, 0xB9); // CMP C
  cpu->C = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_d) {
  write_byte(cpu, 0, 0xBA); // CMP D
  cpu->D = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_e) {
  write_byte(cpu, 0, 0xBB); // CMP E
  cpu->E = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_h) {
  write_byte(cpu, 0, 0xBC); // CMP H
  cpu->H = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_l) {
  write_byte(cpu, 0, 0xBD); // CMP L
  cpu->L = 1; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_m) {
  write_byte(cpu, 0, 0xBE); // CMP E
  write_byte(cpu, 0x05, 1);
  cpu->H = 0x00; cpu->L = 0x05; cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_a) {
  write_byte(cpu, 0, 0xBF); // CMP A
  cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

// Bit flag tests
TEST_CASE(cmp_less) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x0A; cpu->B = 0x05;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cmp_greater) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x02; cpu->B = 0x0A;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cmp_not_equal) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0xFF; cpu->B = 0x0A;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_FALSE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(cmp_equal) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x0A; cpu->B = 0x0A;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(cmp_sets_s_flag) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(cmp_sets_p_flag) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0x04;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(cmp_sets_c_flag) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x00; cpu->B = 0x01;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

// Comparisons with 0 are tricky
// https://retrocomputing.stackexchange.com/questions/6407/intel-8080-behaviour-of-the-carry-bit-when-comparing-a-value-with-0
TEST_CASE(cmp_compare_with_0) {
  write_byte(cpu, 0, 0xB8); // CMP B
  cpu->A = 0x01; cpu->B = 0x00;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}