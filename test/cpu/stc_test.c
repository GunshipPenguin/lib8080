#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_stc);
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
