#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_mvi);
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

TEST_CASE(sub_b) {
  write8(0, 0x90);
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_c) {
  write8(0, 0x91);
  cpu->C = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_d) {
  write8(0, 0x92);
  cpu->D = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_e) {
  write8(0, 0x93);
  cpu->E = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_h) {
  write8(0, 0x94);
  cpu->H = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_l) {
  write8(0, 0x95);
  cpu->L = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_m) {
  write8(0, 0x96);
  write8(8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(sub_a) {
  write8(0, 0x97);
  cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 1);
}