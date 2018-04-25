#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_inx);
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
    write8(i, 0);
  }
}
AFTER_EACH() {}

TEST_CASE(jmp) {
  write8(0, 0xC3); // JMP
  write16(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jmp_alternate_0xcb) {
  write8(0, 0xCB); // JMP
  write16(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}