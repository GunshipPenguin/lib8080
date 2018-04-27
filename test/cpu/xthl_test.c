#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_xthl);
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

TEST_CASE(xthl) {
  write_byte(0, 0xE3); // XTHL

  cpu->SP = 10;
  write_byte(10, 0xAB);
  write_byte(11, 0xCD);
  cpu->H = 0x01; cpu->L = 0x02;

  step_cpu();

  ASSERT_EQUAL(cpu->L, 0xAB);
  ASSERT_EQUAL(cpu->H, 0xCD);
  ASSERT_EQUAL(read_byte(10), 0x02);
  ASSERT_EQUAL(read_byte(11), 0x01);
}