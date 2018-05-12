#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(carry_bit_instructions);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(stc) {
  write_byte(0, 0x37); // STC
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_TRUE(get_flag(FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(cmc) {
  write_byte(0, 0x3F); // CMC
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_FALSE(get_flag(FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}
