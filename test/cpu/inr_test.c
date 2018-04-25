#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_inr);
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
TEST_CASE(inr_b) {
  write8(0, 0x04);
  cpu->B = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->B, 1);
}


TEST_CASE(inr_c) {
  write8(0, 0x0C);
  cpu->C = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_d) {
  write8(0, 0x14);
  cpu->B = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_e) {
  write8(0, 0x1C);
  cpu->C = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_h) {
  write8(0, 0x24);
  cpu->H = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_l) {
  write8(0, 0x2C);
  cpu->L = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inr_m) {
  write8(0, 0x34);
  write8(0x08, 0);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read8(CONCAT(cpu->H, cpu->L)), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(inr_a) {
  write8(0, 0x3C);
  cpu->A = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Flag bit tests
TEST_CASE(inr_sets_z_flag) {
  write8(0, 0x3C); // INR A
  cpu->A = 0xFF;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(inr_sets_p_flag) {
  write8(0, 0x3C); // INR A
  cpu->A = 0x00;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 1);
}

TEST_CASE(inr_sets_s_flag) {
  write8(0, 0x3C); // INR A
  cpu->A = 0x7F;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(inr_sets_a_flag) {
  write8(0, 0x3C); // INR A
  cpu->A = 0x0F;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}