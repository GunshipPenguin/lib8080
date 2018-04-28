#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_xchg);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(xchg) {
  write_byte(0, 0xEB); // XCHG
  cpu->H = 1; cpu->L = 2;
  cpu->D = 3; cpu->E = 4;

  step_cpu();

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->E, 2);
  ASSERT_EQUAL(cpu->H, 3);
  ASSERT_EQUAL(cpu->L, 4);
}