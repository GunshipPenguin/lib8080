#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_sub);
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

// Individual opcode tests
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

// Flag bit tests
TEST_CASE(sub_sets_z_flag) {
  write8(0, 0x90); // ADD B
  cpu->A = 0x01; cpu->B = 0x01;
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(sub_sets_p_flag) {
  write8(0, 0x90); // SUB B
  cpu->A = 0x03; cpu->B = 0x01;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 1);
}

TEST_CASE(sub_sets_s_flag) {
  write8(0, 0x90); // SUB B
  cpu->A = 0xFF; cpu->B = 0x01;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(sub_sets_a_flag) {
  write8(0, 0x90); // SUB B
  cpu->A = 0x10; cpu->B = 0x01;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}

TEST_CASE(sub_sets_c_flag) {
  write8(0, 0x90); // SUB B
  cpu->A = 0x00; cpu->B = 0x01;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_C), 1);
}