#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_dcr);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(dcr_b) {
  write_byte(cpu, 0, 0x05);
  cpu->B = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->B, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_c) {
  write_byte(cpu, 0, 0x0D);
  cpu->C = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->C, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_d) {
  write_byte(cpu, 0, 0x15);
  cpu->D = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->D, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_e) {
  write_byte(cpu, 0, 0x1D);
  cpu->E = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->E, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_h) {
  write_byte(cpu, 0, 0x25);
  cpu->H = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->H, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_l) {
  write_byte(cpu, 0, 0x2D);
  cpu->L = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->L, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_m) {
  write_byte(cpu, 0, 0x35);
  write_byte(cpu, 0x08, 1);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu(cpu);

  ASSERT_EQUAL(read_byte(cpu, 0x08), 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(dcr_a) {
  write_byte(cpu, 0, 0x3D);
  cpu->A = 1;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

// Edge case tests
TEST_CASE(dcr_wraps_0_to_0xff) {
  write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0;

  step_cpu(cpu);
  ASSERT_EQUAL(cpu->A, 0xFF);
}

// Flag bit tests
TEST_CASE(dcr_sets_z_flag) {
  write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x01;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(dcr_sets_p_flag) {
  write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x03;
  set_flag(cpu, FLAG_P, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_P));
}

TEST_CASE(dcr_sets_s_flag) {
  write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x00;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(dcr_sets_a_flag) {
  write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x1;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}