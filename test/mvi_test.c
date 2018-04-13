#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(opcode_mvi);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }

  reset_cpu();
  cpu->PC = 0;

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write8(i, 0);
  }
}
AFTER_EACH() {}

TEST_CASE(mvi_b_d8) {
  write8(0, 0x06);
  write8(1, 0x01);
  cpu->B = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->B, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_c_d8) {
  write8(0, 0x0E);
  write8(1, 0x01);
  cpu->C = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_d_d8) {
  write8(0, 0x16);
  write8(1, 0x01);
  cpu->D = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_e_d8) {
  write8(0, 0x1E);
  write8(1, 0x01);
  cpu->E = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_h_d8) {
  write8(0, 0x26);
  write8(1, 0x01);
  cpu->H = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_l_d8) {
  write8(0, 0x2E);
  write8(1, 0x01);
  cpu->L = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_m_d8) {
  write8(0, 0x36);
  write8(1, 0x01);
  cpu->H = 0x00; cpu->L = 0x08;

  step_cpu();

  ASSERT_EQUAL(read8(8), 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_a_d8) {
  write8(0, 0x3E);
  write8(1, 0x01);
  cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}