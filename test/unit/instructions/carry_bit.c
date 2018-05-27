#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(carry_bit_instructions);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(stc_carry_0) {
  i8080_write_byte(cpu, 0, 0x37); // STC
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(stc_carry_1) {
  i8080_write_byte(cpu, 0, 0x37); // STC
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmc_carry_1) {
  i8080_write_byte(cpu, 0, 0x3F); // CMC
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(cmc_carry_0) {
  i8080_write_byte(cpu, 0, 0x3F); // CMC
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}
