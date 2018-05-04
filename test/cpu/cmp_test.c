#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_cmp);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(cmp_b) {
  write_byte(0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_c) {
  write_byte(0, 0xB9); // CMP C
  cpu->C = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_d) {
  write_byte(0, 0xBA); // CMP D
  cpu->D = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_e) {
  write_byte(0, 0xBB); // CMP E
  cpu->E = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_h) {
  write_byte(0, 0xBC); // CMP H
  cpu->H = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_l) {
  write_byte(0, 0xBD); // CMP L
  cpu->L = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_m) {
  write_byte(0, 0xBE); // CMP E
  write_byte(0x05, 1);
  cpu->H = 0x00; cpu->L = 0x05; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_a) {
  write_byte(0, 0xBF); // CMP A
  cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 1);
}

// Bit flag tests
TEST_CASE(cmp_sets_z_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
}

TEST_CASE(cmp_sets_s_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0xFF;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_S));
}

TEST_CASE(cmp_sets_p_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0x04;

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_P));
}

TEST_CASE(cmp_sets_c_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->A = 0x00; cpu->B = 0x01;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_C));
}

TEST_CASE(cmp_resets_c_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->A = 0x01; cpu->B = 0x01;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_FALSE(get_flag(FLAG_C));
}

TEST_CASE(cmp_sets_a_flag) {
  write_byte(0, 0xB8); // CMP B
  cpu->A = 0xFF; cpu->B = 0x01;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_A));
}
