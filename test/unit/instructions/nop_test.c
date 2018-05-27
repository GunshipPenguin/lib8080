#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_nop);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(nop_0x00) {
  i8080_write_byte(cpu, 0, 0x00);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x08) {
  i8080_write_byte(cpu, 0, 0x08);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x10) {
  i8080_write_byte(cpu, 0, 0x10);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x18) {
  i8080_write_byte(cpu, 0, 0x18);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x20) {
  i8080_write_byte(cpu, 0, 0x20);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x28) {
  i8080_write_byte(cpu, 0, 0x28);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x30) {
  i8080_write_byte(cpu, 0, 0x00);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(nop_0x38) {
  i8080_write_byte(cpu, 0, 0x38);
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}