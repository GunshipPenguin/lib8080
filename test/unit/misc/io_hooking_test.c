#include "cpu_test_helpers.h"
#include "i8080.h"
#include "attounit.h"

struct i8080 *cpu;
int in_handler_called;
uint in_handler_dev_arg;
uint in_handler_retval;

int out_handler_called;
uint out_handler_dev_arg;
uint out_handler_data_arg;

TEST_SUITE(io_hooking)
BEFORE_EACH() {
  in_handler_called = 0;
  in_handler_dev_arg = 0xFFFF;
  in_handler_retval = 0xFFFF;

  out_handler_called = 0;
  out_handler_dev_arg = 0xFFFF;
  out_handler_data_arg = 0xFFFF;

  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

uint in_handler(uint dev) {
  in_handler_called = 1;
  in_handler_dev_arg = dev;

  return in_handler_retval;
}

void out_handler(uint dev, uint data) {
  out_handler_called = 1;
  out_handler_dev_arg = dev;
  out_handler_data_arg = data;
}

TEST_CASE(hook_input) {
  write_byte(cpu, 0, 0xDB); // IN
  write_byte(cpu, 1, 0xAB); // d8
  in_handler_retval = 0xCD;
  cpu->input_handler = in_handler;

  step_cpu(cpu);

  ASSERT_TRUE(in_handler_called);
  ASSERT_EQUAL(in_handler_dev_arg, 0xAB);
  ASSERT_EQUAL(cpu->A, 0xCD);
}

TEST_CASE(hook_output) {
  write_byte(cpu, 0, 0xD3); // OUT
  write_byte(cpu, 1, 0xAB); // d8
  cpu->A = 0xCD;
  cpu->output_handler = out_handler;

  step_cpu(cpu);

  ASSERT_TRUE(out_handler_called);
  ASSERT_EQUAL(out_handler_dev_arg, 0xAB);
  ASSERT_EQUAL(out_handler_data_arg, 0xCD);
}
