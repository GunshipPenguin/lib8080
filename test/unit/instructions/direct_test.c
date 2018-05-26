#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instructions_direct_addressing);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(lda) {
  write_byte(cpu, 0, 0x3A); // LDA
  write_word(cpu, 1, 5); // a16
  write_byte(cpu, 5, 1);
  cpu->A = 0x00;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 13);
}

TEST_CASE(sta) {
  write_byte(cpu, 0, 0x32); // STA
  write_word(cpu, 1, 5); // a16
  cpu->A = 0x01;

  step_cpu(cpu);

  ASSERT_EQUAL(read_byte(cpu, 5), 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 13);
}

TEST_CASE(shld) {
  write_byte(cpu, 0, 0x22); // SHLD
  write_word(cpu, 1, 0x05);
  cpu->H = 0x02; cpu->L = 0x01;

  step_cpu(cpu);

  ASSERT_EQUAL(read_byte(cpu, 0x05), 0x01);
  ASSERT_EQUAL(read_byte(cpu, 0x06), 0x02);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 16);
}

TEST_CASE(lhld) {
  write_byte(cpu, 0, 0x2A); // LDHD
  write_word(cpu, 1, 0x05);
  write_word(cpu, 0x05, 0xABCD);
  cpu->H = 0x00; cpu->L = 0x00;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 16);
}