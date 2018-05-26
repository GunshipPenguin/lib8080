#include "cpu_test_helpers.h"
#include "i8080.h"
#include "attounit.h"

struct i8080 *cpu;

TEST_SUITE(io_instructions)
BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(in_no_handler) {
  write_byte(cpu, 0, 0xDB); // IN
  write_byte(cpu, 1, 0); // d8

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(out_no_handler) {
  write_byte(cpu, 0, 0xD3); // OUT
  write_byte(cpu, 1, 0); // d8

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 2);
}