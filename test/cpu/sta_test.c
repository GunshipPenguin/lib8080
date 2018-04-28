#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sta);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(sta) {
  write_byte(0, 0x32); // STA
  write_word(1, 5); // a16
  cpu->A = 0x01;

  step_cpu();

  ASSERT_EQUAL(read_byte(5), 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
}