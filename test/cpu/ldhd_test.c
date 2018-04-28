#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_ldhd);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(ldhd) {
  write_byte(0, 0x2A); // LDHD
  write_word(1, 0x05);
  write_word(0x05, 0xABCD);
  cpu->H = 0x00; cpu->L = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->PC, 3);
}