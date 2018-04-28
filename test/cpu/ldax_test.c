#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_ldax);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(ldax_b) {
  write_byte(0, 0x0A); // LDAX B
  write_byte(5, 0x01);
  cpu->A = 0x00; cpu->B = 0x00; cpu->C = 0x05;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(ldax_d) {
  write_byte(0, 0x1A); // LDAX D
  write_byte(5, 0x01);
  cpu->A = 0x00; cpu->D = 0x00; cpu->E = 0x05;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
}