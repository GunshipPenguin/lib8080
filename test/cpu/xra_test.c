#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_xra);
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
    write_byte(i, 0);
  }
}
AFTER_EACH() {}

// Individual opcode tests
TEST_CASE(xra_b) {
  write_byte(0, 0xA8); // XRA B
  cpu->B = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_c) {
  write_byte(0, 0xA9); // XRA C
  cpu->C = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_d) {
  write_byte(0, 0xAA); // XRA D
  cpu->D = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_e) {
  write_byte(0, 0xAB); // XRA E
  cpu->E = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_h) {
  write_byte(0, 0xAC); // XRA H
  cpu->H = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_l) {
  write_byte(0, 0xAD); // XRA L
  cpu->L = 0xFF; cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_m) {
  write_byte(0, 0xAE); // XRA M
  write_byte(0x05, 0xFF);
  cpu->A = 0xF0; cpu->H = 0x00; cpu->L = 0x05;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(xra_a) {
  write_byte(0, 0xAF); // XRA A
  cpu->A = 0xF0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x00);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Bit flag tests
TEST_CASE(xra_clears_flag_c_and_a) {
  write_byte(0, 0xA8); // XRA B
  set_flag(FLAG_C, 1);
  set_flag(FLAG_A, 1);

  step_cpu();

  ASSERT_FALSE(get_flag(FLAG_C));
  ASSERT_FALSE(get_flag(FLAG_A));
}

TEST_CASE(xra_sets_flag_z) {
  write_byte(0, 0xA8); // XRA B
  cpu->A = 0xFF; cpu->B = 0xFF;
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_Z));
}

TEST_CASE(xra_sets_flag_s) {
  write_byte(0, 0xA8); // XRA B
  cpu->A = 0x7F; cpu->B = 0xFF;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_S));
}

TEST_CASE(xra_sets_flag_p) {
  write_byte(0, 0xA8); // XRA B
  cpu->A = 0x04; cpu->B = 0x07;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_P));
}