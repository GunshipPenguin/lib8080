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
}

TEST_CASE(inr_d) {
  write8(0, 0x14);
  cpu->B = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 1);
}


TEST_CASE(inr_e) {
  write8(0, 0x1C);
  cpu->C = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 1);
}

TEST_CASE(inr_h) {
  write8(0, 0x24);
  cpu->H = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 1);
}


TEST_CASE(inr_l) {
  write8(0, 0x2C);
  cpu->L = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 1);
}

TEST_CASE(inr_m) {
  write8(0, 0x34);
  write8(0x08, 0);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read8(CONCAT(cpu->H, cpu->L)), 1);
}


TEST_CASE(inr_a) {
  write8(0, 0x3C);
  cpu->A = 0;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 1);
}