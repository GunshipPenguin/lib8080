#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_dcr);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(dcr_b) {
  write_byte(0, 0x05);
  cpu->B = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->B, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_c) {
  write_byte(0, 0x0D);
  cpu->C = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->C, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_d) {
  write_byte(0, 0x15);
  cpu->D = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_e) {
  write_byte(0, 0x1D);
  cpu->E = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_h) {
  write_byte(0, 0x25);
  cpu->H = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_l) {
  write_byte(0, 0x2D);
  cpu->L = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_m) {
  write_byte(0, 0x35);
  write_byte(0x08, 1);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read_byte(CONCAT(cpu->H, cpu->L)), 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_a) {
  write_byte(0, 0x3D);
  cpu->A = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Edge case tests
TEST_CASE(dcr_wraps_0_to_0xff) {
  write_byte(0, 0x3D); // DCR A
  cpu->A = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 0xFF);
}

// Flag bit tests
TEST_CASE(dcr_sets_z_flag) {
  write_byte(0, 0x3D); // DCR A
  cpu->A = 0x01;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(dcr_sets_p_flag) {
  write_byte(0, 0x3D); // DCR A
  cpu->A = 0x03;
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 0);
}

TEST_CASE(dcr_sets_s_flag) {
  write_byte(0, 0x3D); // DCR A
  cpu->A = 0x00;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(dcr_sets_a_flag) {
  write_byte(0, 0x3D); // DCR A
  cpu->A = 0xF0;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}