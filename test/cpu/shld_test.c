#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_shld);
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

TEST_CASE(shld) {
  write_byte(0, 0x22); // SHLD
  write_word(1, 0x05);
  cpu->H = 0x02; cpu->L = 0x01;

  step_cpu();

  ASSERT_EQUAL(read_byte(0x05), 0x01);
  ASSERT_EQUAL(read_byte(0x06), 0x02);
  ASSERT_EQUAL(cpu->PC, 3);
}