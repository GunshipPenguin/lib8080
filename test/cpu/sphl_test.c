#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_sphl);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(sphl) {
  write_byte(0, 0xF9); // SPHL
  cpu->H = 0xAB; cpu->L = 0xCD;
  cpu->SP = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
}