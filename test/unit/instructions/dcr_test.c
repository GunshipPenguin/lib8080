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
  i8080_write_byte(cpu, 0, 0x05);
  cpu->B = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->B, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_c) {
  i8080_write_byte(cpu, 0, 0x0D);
  cpu->C = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->C, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_d) {
  i8080_write_byte(cpu, 0, 0x15);
  cpu->D = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->D, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_e) {
  i8080_write_byte(cpu, 0, 0x1D);
  cpu->E = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->E, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_h) {
  i8080_write_byte(cpu, 0, 0x25);
  cpu->H = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->H, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcr_l) {
  i8080_write_byte(cpu, 0, 0x2D);
  cpu->L = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->L, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcr_m) {
  i8080_write_byte(cpu, 0, 0x35);
  i8080_write_byte(cpu, 0x08, 1);
  cpu->H = 0; cpu->L = 0x08;

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_read_byte(cpu, 0x08), 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(dcr_a) {
  i8080_write_byte(cpu, 0, 0x3D);
  cpu->A = 1;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

// Edge case tests
TEST_CASE(dcr_wraps_0_to_0xff) {
  i8080_write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0;

  i8080_step(cpu);
  ASSERT_EQUAL(cpu->A, 0xFF);
}

// i8080_flag bit tests
TEST_CASE(dcr_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x01;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(dcr_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x03;
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(dcr_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(dcr_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0x3D); // DCR A
  cpu->A = 0x1;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}