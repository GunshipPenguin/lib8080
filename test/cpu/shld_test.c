#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_shld);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(shld) {
  write_byte(0, 0x22); // SHLD
  write_word(1, 0x05);
  cpu->H = 0x02; cpu->L = 0x01;

  step_cpu();

  ASSERT_EQUAL(read_byte(0x05), 0x01);
  ASSERT_EQUAL(read_byte(0x06), 0x02);
  ASSERT_EQUAL(cpu->PC, 3);
}