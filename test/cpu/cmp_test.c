#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_cmp);
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
TEST_CASE(cmp_b) {
  write8(0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_c) {
  write8(0, 0xB9); // CMP C
  cpu->C = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_d) {
  write8(0, 0xBA); // CMP D
  cpu->D = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_e) {
  write8(0, 0xBB); // CMP E
  cpu->E = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_h) {
  write8(0, 0xBC); // CMP H
  cpu->H = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_l) {
  write8(0, 0xBD); // CMP L
  cpu->L = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_m) {
  write8(0, 0xBE); // CMP E
  write8(0x05, 1);
  cpu->H = 0x00; cpu->L = 0x05; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmp_a) {
  write8(0, 0xBF); // CMP A
  cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Bit flag tests
TEST_CASE(cmp_sets_z_flag) {
  write8(0, 0xB8); // CMP B
  cpu->B = 1; cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(cmp_sets_s_flag) {
  write8(0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0xFF;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(cmp_sets_p_flag) {
  write8(0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0x03;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 1);
}

TEST_CASE(cmp_sets_c_flag) {
  write8(0, 0xB8); // CMP B
  cpu->B = 0xFF; cpu->A = 0x01;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_C), 1);
}

TEST_CASE(cmp_sets_a_flag) {
  write8(0, 0xB8); // CMP B
  cpu->B = 0x01; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}
