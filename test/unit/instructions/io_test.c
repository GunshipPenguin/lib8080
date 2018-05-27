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
  i8080_write_byte(cpu, 0, 0xDB); // IN
  i8080_write_byte(cpu, 1, 0); // d8

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(out_no_handler) {
  i8080_write_byte(cpu, 0, 0xD3); // OUT
  i8080_write_byte(cpu, 1, 0); // d8

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->cyc, 10);
}