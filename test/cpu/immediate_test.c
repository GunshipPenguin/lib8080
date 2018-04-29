#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(immediate_addressing_instructions);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(mvi_b_d8) {
  write_byte(0, 0x06);
  write_byte(1, 0x01);
  cpu->B = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->B, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_c_d8) {
  write_byte(0, 0x0E);
  write_byte(1, 0x01);
  cpu->C = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_d_d8) {
  write_byte(0, 0x16);
  write_byte(1, 0x01);
  cpu->D = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_e_d8) {
  write_byte(0, 0x1E);
  write_byte(1, 0x01);
  cpu->E = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_h_d8) {
  write_byte(0, 0x26);
  write_byte(1, 0x01);
  cpu->H = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_l_d8) {
  write_byte(0, 0x2E);
  write_byte(1, 0x01);
  cpu->L = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_m_d8) {
  write_byte(0, 0x36);
  write_byte(1, 0x01);
  cpu->H = 0x00; cpu->L = 0x08;

  step_cpu();

  ASSERT_EQUAL(read_byte(8), 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_a_d8) {
  write_byte(0, 0x3E);
  write_byte(1, 0x01);
  cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(lxi_b_d16) {
  write_byte(0, 0x01); // LXI B
  write_word(1, 0xABCD); // d16
  cpu->B = 0x00; cpu->C = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->B, 0xAB);
  ASSERT_EQUAL(cpu->C, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_d_d16) {
  write_byte(0, 0x11); // LXI D
  write_word(1, 0xABCD); // d16
  cpu->D = 0x00; cpu->E = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 0xAB);
  ASSERT_EQUAL(cpu->E, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_h_d16) {
  write_byte(0, 0x21); // LXI H
  write_word(1, 0xABCD); // d16
  cpu->H = 0x00; cpu->L = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_sp_d16) {
  write_byte(0, 0x31); // LXI B
  write_word(1, 0xABCD); // d16
  cpu->SP = 0x0000;

  step_cpu();

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 3);
}
