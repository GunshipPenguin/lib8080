#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(immediate_addressing_instructions);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(mvi_b_d8) {
  i8080_write_byte(cpu, 0, 0x06); // MVI B
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->B = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->B, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_c_d8) {
  i8080_write_byte(cpu, 0, 0x0E); // MVI C
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->C = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_d_d8) {
  i8080_write_byte(cpu, 0, 0x16); // MVI D
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->D = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_e_d8) {
  i8080_write_byte(cpu, 0, 0x1E); // MVI E
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->E = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_h_d8) {
  i8080_write_byte(cpu, 0, 0x26); // MVI H
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->H = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_l_d8) {
  i8080_write_byte(cpu, 0, 0x2E); // MVI L
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->L = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(mvi_m_d8) {
  i8080_write_byte(cpu, 0, 0x36); // MVI M
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->H = 0x00; cpu->L = 0x08;

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_read_byte(cpu, 8), 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(mvi_a_d8) {
  i8080_write_byte(cpu, 0, 0x3E); // MVI A
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(lxi_b_d16) {
  i8080_write_byte(cpu, 0, 0x01); // LXI B
  i8080_write_word(cpu, 1, 0xABCD); // d16
  cpu->B = 0x00; cpu->C = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->B, 0xAB);
  ASSERT_EQUAL(cpu->C, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(lxi_d_d16) {
  i8080_write_byte(cpu, 0, 0x11); // LXI D
  i8080_write_word(cpu, 1, 0xABCD); // d16
  cpu->D = 0x00; cpu->E = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 0xAB);
  ASSERT_EQUAL(cpu->E, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(lxi_h_d16) {
  i8080_write_byte(cpu, 0, 0x21); // LXI H
  i8080_write_word(cpu, 1, 0xABCD); // d16
  cpu->H = 0x00; cpu->L = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(lxi_sp_d16) {
  i8080_write_byte(cpu, 0, 0x31); // LXI B
  i8080_write_word(cpu, 1, 0xABCD); // d16
  cpu->SP = 0x0000;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(adi) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(adi_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(adi_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI
  i8080_write_byte(cpu, 1, 0); // d8

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(adi_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 2;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(adi_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI B
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x7F;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(adi_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xC6); // ADI
  i8080_write_byte(cpu, 1, 1);
  cpu->A = 0x0F;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(aci) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(aci_unsets_c_flag) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI B
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 2;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(aci_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI
  i8080_write_byte(cpu, 1, 0); // d8
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);
  
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(aci_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x02;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(aci_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x7F;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(aci_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xCE); // ACI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x0F;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(sui) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(sui_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x00;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(sui_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(sui_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(sui_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(sui_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x04;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(sui_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xD6); // SUI
  i8080_write_byte(cpu, 1, 1);
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(sbi) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 0x0F); // d8
  cpu->A = 0xF0;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(sbi_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(sbi_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 4;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(sbi_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 1);
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(sbi_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(sbi_subtrahend_0xFF_with_borrow) {
  i8080_write_byte(cpu, 0, 0xDE); // SBI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xAB;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xAB);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_A));
}


TEST_CASE(ani) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 6); // d8
  cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(ani_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(ani_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 0); // d8
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(ani_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 3); // d8
  cpu->A = 7;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(ani_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

// On the 8080, logical and instructions set the aux carry flag to the logical
// or of bit 3 of the values involved in the operation
TEST_CASE(ani_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 0xF0); // d8
  cpu->A = 0x08;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(ani_resets_a_flag) {
  i8080_write_byte(cpu, 0, 0xE6); // ANI
  i8080_write_byte(cpu, 1, 0x07); // d8
  cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(ori) {
  i8080_write_byte(cpu, 0, 0xF6); // ORI
  i8080_write_byte(cpu, 1, 6); // d8
  cpu->A = 10;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(ori_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xF6); // ORI
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(ori_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0xF6); // ORI
  i8080_write_byte(cpu, 1, 0); // d8
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(ori_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xF6); // ORI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(ori_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xF6); // ORI
  i8080_write_byte(cpu, 1, 3); // d8
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(xri) {
  i8080_write_byte(cpu, 0, 0xEE); // XRI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(xri_resets_flag_c) {
  i8080_write_byte(cpu, 0, 0xEE); // XRI
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(xri_sets_flag_z) {
  i8080_write_byte(cpu, 0, 0xEE); // XRI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(xri_sets_flag_s) {
  i8080_write_byte(cpu, 0, 0xEE); // XRI
  i8080_write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0x7F;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(xri_sets_flag_p) {
  i8080_write_byte(cpu, 0, 0xEE); // XRI
  i8080_write_byte(cpu, 1, 7); // d8
  cpu->A = 0x04;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(cpi) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(cpi_less) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0x0A;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_greater) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0x02;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_not_equal) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(cpi_equal) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x0A); // d8
  cpu->A = 0x0A;

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(cpi_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0xFF;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(cpi_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x04;

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(cpi_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0x00;
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0x01;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

// Comparisons with 0 are tricky
// https://retrocomputing.stackexchange.com/questions/6407/intel-8080-behaviour-of-the-carry-bit-when-comparing-a-value-with-0
TEST_CASE(cpi_compare_with_0) {
  i8080_write_byte(cpu, 0, 0xFE); // CPI
  i8080_write_byte(cpu, 1, 0); // d8
  cpu->A = 0x01;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}