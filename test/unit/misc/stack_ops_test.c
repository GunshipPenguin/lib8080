#include "i8080.h"
#include "attounit.h"
#include "cpu_test_helpers.h"

TEST_SUITE(stack_operations)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}


TEST_CASE(stack_push_pop_byte) {
  i8080_push_stackb(cpu, 0xAB);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 0xAB);
}

TEST_CASE(stack_push_pop_word) {
  i8080_push_stackw(cpu, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackw(cpu), 0xABCD);
}