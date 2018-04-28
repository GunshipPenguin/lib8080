#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_lda);
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