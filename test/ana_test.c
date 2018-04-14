#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_ana);
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

TEST_CASE(ana_b) {
  write8(0, 0xA0);
  cpu->B = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_c) {
  write8(0, 0xA1);
  cpu->C = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_d) {
  write8(0, 0xA2);
  cpu->D = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_e) {
  write8(0, 0xA3);
  cpu->E = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_h) {
  write8(0, 0xA4);
  cpu->H = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_l) {
  write8(0, 0xA5);
  cpu->L = 6; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_m) {
  write8(0, 0xA6);
  write8(8, 6);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(ana_a) {
  write8(0, 0xA7);
  cpu->A = 10;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 10);
  ASSERT_EQUAL(cpu->PC, 1);
}