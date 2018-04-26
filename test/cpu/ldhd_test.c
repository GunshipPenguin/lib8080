#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_ldhd);
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