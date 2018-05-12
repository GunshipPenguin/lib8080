#include "unit/attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instructions_direct_addressing);
BEFORE_EACH() {
  setup_cpu_test_env();
}
AFTER_EACH() {}

TEST_CASE(lda) {
  write_byte(0, 0x3A); // LDA
  write_word(1, 5); // a16
  write_byte(5, 1);
  cpu->A = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(sta) {
  write_byte(0, 0x32); // STA
  write_word(1, 5); // a16
  cpu->A = 0x01;

  step_cpu();

  ASSERT_EQUAL(read_byte(5), 0x01);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(shld) {
  write_byte(0, 0x22); // SHLD
  write_word(1, 0x05);
  cpu->H = 0x02; cpu->L = 0x01;

  step_cpu();

  ASSERT_EQUAL(read_byte(0x05), 0x01);
  ASSERT_EQUAL(read_byte(0x06), 0x02);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(ldhd) {
  write_byte(0, 0x2A); // LDHD
  write_word(1, 0x05);
  write_word(0x05, 0xABCD);
  cpu->H = 0x00; cpu->L = 0x00;

  step_cpu();

  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->PC, 3);
}