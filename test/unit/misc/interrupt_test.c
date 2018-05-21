#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(interrupts)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(interrupt_request_inte_set) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_0);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 0);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_inte_unset) {
  cpu->PC = 60;
  cpu->SP = 16;
  cpu->INTE = 0;

  write_byte(cpu, 60, 0x00); // NOP
  request_interrupt(cpu, I8080_RST_0);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 61);
  ASSERT_EQUAL(cpu->SP, 16);
}

TEST_CASE(interrupt_request_rst_1) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_1);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 8);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_2) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_2);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 16);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_3) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_3);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 24);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_4) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_4);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 32);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_5) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_5);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 40);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_6) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_6);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 48);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}

TEST_CASE(interrupt_request_rst_7) {
  cpu->PC = 60;
  cpu->INTE = 1;
  request_interrupt(cpu, I8080_RST_7);

  step_cpu(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 56);
  ASSERT_EQUAL(pop_stackw(cpu), 60);
}