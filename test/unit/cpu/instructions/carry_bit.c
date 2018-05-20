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
  write_byte(cpu, 0, 0x37); // STC
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(stc_carry_1) {
  write_byte(cpu, 0, 0x37); // STC
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmc_carry_1) {
  write_byte(cpu, 0, 0x3F); // CMC
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmc_carry_0) {
  write_byte(cpu, 0, 0x3F); // CMC
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}
