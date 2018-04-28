#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_rar);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(rar_low_bit_one_carry_zero) {
  write_byte(0, 0x1F); // RAR
  cpu->A = 0xFF;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x7F);
  ASSERT_EQUAL(get_flag(FLAG_C), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rar_low_bit_zero_carry_zero) {
  write_byte(0, 0x1F); // RAR
  cpu->A = 0xFE;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x7F);
  ASSERT_EQUAL(get_flag(FLAG_C), 0);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rar_low_bit_one_carry_one) {
  write_byte(0, 0x1F); // RAR
  cpu->A = 0xFF;
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_EQUAL(get_flag(FLAG_C), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}