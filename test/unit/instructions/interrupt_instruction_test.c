#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(interrupt_instructions)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(ei) {
  i8080_write_byte(cpu, 0, 0xFB);

  i8080_step(cpu);

  ASSERT_TRUE(cpu->INTE);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(di) {
  i8080_write_byte(cpu, 0, 0xF3);
  cpu->INTE = 1;

  i8080_step(cpu);

  ASSERT_FALSE(cpu->INTE);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(rst_0) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xC7); // RST 0

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 0);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_1) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xCF); // RST 1

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 8);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_2) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xD7); // RST 2

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 16);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_3) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xDF); // RST 3

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 24);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_4) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xE7); // RST 4

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 32);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_5) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xEF); // RST 5

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 40);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_6) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xF7); // RST 6

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 48);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rst_7) {
  cpu->PC = 60;
  i8080_write_byte(cpu, 60, 0xFF); // RST 7

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 61);
  ASSERT_EQUAL(cpu->PC, 56);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(hlt) {
  cpu->halted = 0;
  cpu->INTE = 1;
  i8080_write_byte(cpu, 0, 0x76); // HLT
  i8080_step(cpu);

  ASSERT_TRUE(cpu->halted);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);

  i8080_request_interrupt(cpu, I8080_RST_7);

  i8080_step(cpu);

  ASSERT_FALSE(cpu->halted);
  ASSERT_EQUAL(cpu->PC, 56);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 1);
}

TEST_CASE(hlt_cycles) {
  i8080_write_byte(cpu, 0, 0x76); // HLT
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->cyc, 7);
}