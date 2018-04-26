#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_cmc);
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

TEST_CASE(cmc) {
  write_byte(0, 0x3F); // CMC
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_TRUE(!get_flag(FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}
