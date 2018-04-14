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

TEST_CASE(dcr_b) {
  write8(0, 0x05);
  cpu->B = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->B, 0);
}


TEST_CASE(dcr_c) {
  write8(0, 0x0E);
  cpu->C = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->C, 0);
}

TEST_CASE(dcr_d) {
  write8(0, 0x15);
  cpu->D = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->D, 0);
}


TEST_CASE(dcr_e) {
  write8(0, 0x1D);
  cpu->E = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->E, 0);
}

TEST_CASE(dcr_h) {
  write8(0, 0x25);
  cpu->H = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->H, 0);
}


TEST_CASE(dcr_l) {
  write8(0, 0x2D);
  cpu->L = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->L, 0);
}

TEST_CASE(dcr_m) {
  write8(0, 0x35);
  write8(0x08, 1);
  cpu->H = 0; cpu->L = 0x08;

  step_cpu();
  ASSERT_EQUAL(read8(CONCAT(cpu->H, cpu->L)), 0);
}


TEST_CASE(dcr_a) {
  write8(0, 0x3D);
  cpu->A = 1;

  step_cpu();
  ASSERT_EQUAL(cpu->A, 0);
}