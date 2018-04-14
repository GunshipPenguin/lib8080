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

TEST_CASE(add_b) {
  write8(0, 0x80);
  cpu->B = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_c) {
  write8(0, 0x81);
  cpu->C = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_d) {
  write8(0, 0x82);
  cpu->D = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_e) {
  write8(0, 0x83);
  cpu->E = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_h) {
  write8(0, 0x84);
  cpu->H = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_l) {
  write8(0, 0x85);
  cpu->L = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_m) {
  write8(0, 0x86);
  write8(8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_a) {
  write8(0, 0x87);
  cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}