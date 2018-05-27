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
  i8080_request_interrupt(cpu, I8080_RST_0);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 0);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_inte_unset) {
  cpu->PC = 60;
  cpu->SP = 16;
  cpu->INTE = 0;

  i8080_write_byte(cpu, 60, 0x00); // NOP
  i8080_request_interrupt(cpu, I8080_RST_0);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 61);
  ASSERT_EQUAL(cpu->SP, 16);
}

TEST_CASE(interrupt_request_rst_1) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_1);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 8);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_2) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_2);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 16);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_3) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_3);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 24);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_4) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_4);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 32);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_5) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_5);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 40);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_6) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_6);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 48);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}

TEST_CASE(interrupt_request_rst_7) {
  cpu->PC = 60;
  cpu->INTE = 1;
  i8080_request_interrupt(cpu, I8080_RST_7);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->PC, 56);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 60);
}