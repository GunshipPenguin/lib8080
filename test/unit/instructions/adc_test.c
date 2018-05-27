#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_adc);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(adc_b) {
  i8080_write_byte(cpu, 0, 0x88); // ADC B
  cpu->B = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_c) {
  i8080_write_byte(cpu, 0, 0x89); // ADC C
  cpu->C = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_d) {
  i8080_write_byte(cpu, 0, 0x8A); // ADC D
  cpu->D = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_e) {
  i8080_write_byte(cpu, 0, 0x8B); // ADC E
  cpu->E = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_h) {
  i8080_write_byte(cpu, 0, 0x8C); // ADC H
  cpu->H = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_l) {
  i8080_write_byte(cpu, 0, 0x8D); // ADC L
  cpu->L = 0xFF; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(adc_m) {
  i8080_write_byte(cpu, 0, 0x8E); // ADC M
  i8080_write_byte(cpu, 10, 0xFF);
  cpu->H = 0x00; cpu->L = 10; cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(adc_a) {
  i8080_write_byte(cpu, 0, 0x8F); // ADC A
  cpu->A = 0xFF;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// Bit flag tests
TEST_CASE(adc_unsets_c_flag) {
  i8080_write_byte(cpu, 0, 0x88); // ADC B
  cpu->B = 1; cpu->A = 2;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
}

TEST_CASE(adc_sets_z_flag) {
  i8080_write_byte(cpu, 0, 0x88); // ADC B
  cpu->A = 0x00; cpu->B = 0x00;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(adc_sets_p_flag) {
  i8080_write_byte(cpu, 0, 0x88); // ADC B
  cpu->A = 0x02; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}

TEST_CASE(adc_sets_s_flag) {
  i8080_write_byte(cpu, 0, 0x80); // ADC B
  cpu->A = 0x7F; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(adc_sets_a_flag) {
  i8080_write_byte(cpu, 0, 0x8F); // ADC B
  cpu->A = 0x0F; cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_A, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(adc_sets_a_flag_carry_set) {
  i8080_write_byte(cpu, 0, 0x8F); // ADC B
  cpu->A = 0x0D, cpu->B = 0x01;
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
}