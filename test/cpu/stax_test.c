#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_stax);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(stax_b) {
  write_byte(0, 0x02); // STAX B
  cpu->A = 0x01; cpu->B = 0x00; cpu->C = 0x05;

  step_cpu();

  ASSERT_EQUAL(read_byte(5), 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
}


TEST_CASE(stax_d) {
  write_byte(0, 0x12); // STAX D
  cpu->A = 0x01; cpu->D = 0x00; cpu->E = 0x05;

  step_cpu();

  ASSERT_EQUAL(read_byte(5), 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
}