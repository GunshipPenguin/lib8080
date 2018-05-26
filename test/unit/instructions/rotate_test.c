#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(rotate_accumulator_instructions);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(rrc_low_bit_one) {
  write_byte(cpu, 0, 0x0F); // RRC
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(rrc_low_bit_zero) {
  write_byte(cpu, 0, 0x0F); // RRC
  cpu->A = 0xFE;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0x7F);
  ASSERT_FALSE(get_flag(cpu, FLAG_P));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}


TEST_CASE(rar_low_bit_one_carry_zero) {
  write_byte(cpu, 0, 0x1F); // RAR
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0x7F);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(rar_low_bit_zero_carry_zero) {
  write_byte(cpu, 0, 0x1F); // RAR
  cpu->A = 0xFE;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0x7F);
  ASSERT_FALSE(get_flag(cpu, FLAG_P));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(rar_low_bit_one_carry_one) {
  write_byte(cpu, 0, 0x1F); // RAR
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}


TEST_CASE(rlc_high_bit_one) {
  write_byte(cpu, 0, 0x07); // RLC
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(rlc_high_bit_zero) {
  write_byte(cpu, 0, 0x07); // RLC
  cpu->A = 0x7F;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFE);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}


TEST_CASE(ral_high_bit_one_carry_zero) {
  write_byte(cpu, 0, 0x17); // RAL
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFE);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ral_high_bit_zero_carry_zero) {
  write_byte(cpu, 0, 0x17); // RAL
  cpu->A = 0x7F;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFE);
  ASSERT_FALSE(get_flag(cpu, FLAG_P));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(ral_high_bit_one_carry_one) {
  write_byte(cpu, 0, 0x17); // RAL
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}
