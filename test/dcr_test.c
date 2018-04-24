#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_dcr);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }
  reset_cpu();

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write8(i, 0);
  }

  cpu->PC = 0;
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(dcr_b) {
  write8(0, 0x05);
  cpu->B = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->B, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_c) {
  write8(0, 0x0D);
  cpu->C = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->C, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_d) {
  write8(0, 0x15);
  cpu->D = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_e) {
  write8(0, 0x1D);
  cpu->E = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_h) {
  write8(0, 0x25);
  cpu->H = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_l) {
  write8(0, 0x2D);
  cpu->L = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dcr_m) {
  write8(0, 0x35);
  write8(0x08, 1);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read8(CONCAT(cpu->H, cpu->L)), 0);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(dcr_a) {
  write8(0, 0x3D);
  cpu->A = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Edge case tests
TEST_CASE(dcr_wraps_0_to_0xff) {
  write8(0, 0x3D); // DCR A
  cpu->A = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 0xFF);
}

// Flag bit tests
TEST_CASE(dcr_sets_z_flag) {
  write8(0, 0x3D); // DCR A
  cpu->A = 0x01;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(dcr_sets_p_flag) {
  write8(0, 0x3D); // DCR A
  cpu->A = 0x03;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 1);
}

TEST_CASE(dcr_sets_s_flag) {
  write8(0, 0x3D); // DCR A
  cpu->A = 0x00;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(dcr_sets_a_flag) {
  write8(0, 0x3D); // DCR A
  cpu->A = 0xF0;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}