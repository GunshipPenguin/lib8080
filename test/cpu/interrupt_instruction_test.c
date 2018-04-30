#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(interrupt_instructions)
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(ei) {
  write_byte(0, 0xFB);

  step_cpu();

  ASSERT_TRUE(cpu->INTE);
}

TEST_CASE(di) {
  write_byte(0, 0xF3);
  cpu->INTE = 1;

  step_cpu();

  ASSERT_FALSE(cpu->INTE);
}

TEST_CASE(rst_0) {
  cpu->PC = 60;
  write_byte(60, 0xC7); // RST 0

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 0);
}

TEST_CASE(rst_1) {
  cpu->PC = 60;
  write_byte(60, 0xCF); // RST 1

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 8);
}

TEST_CASE(rst_2) {
  cpu->PC = 60;
  write_byte(60, 0xD7); // RST 2

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 16);
}

TEST_CASE(rst_3) {
  cpu->PC = 60;
  write_byte(60, 0xDF); // RST 3

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 24);
}

TEST_CASE(rst_4) {
  cpu->PC = 60;
  write_byte(60, 0xE7); // RST 4

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 32);
}

TEST_CASE(rst_5) {
  cpu->PC = 60;
  write_byte(60, 0xEF); // RST 5

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 40);
}

TEST_CASE(rst_6) {
  cpu->PC = 60;
  write_byte(60, 0xF7); // RST 6

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 48);
}

TEST_CASE(rst_7) {
  cpu->PC = 60;
  write_byte(60, 0xFF); // RST 7

  step_cpu();

  ASSERT_EQUAL(pop_stackw(), 61);
  ASSERT_EQUAL(cpu->PC, 56);
}
