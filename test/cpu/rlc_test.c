#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_rlc);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }

  reset_cpu();
  cpu->PC = 0;

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write_byte(i, 0);
  }
}
AFTER_EACH() {}

TEST_CASE(rlc_high_bit_one) {
  write_byte(0, 0x07); // RLC
  cpu->A = 0xFF;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_EQUAL(get_flag(FLAG_C), 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rlc_high_bit_zero) {
  write_byte(0, 0x07); // RLC
  cpu->A = 0x7F;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->A, 0xFE);
  ASSERT_EQUAL(get_flag(FLAG_C), 0);
  ASSERT_EQUAL(cpu->PC, 1);
}