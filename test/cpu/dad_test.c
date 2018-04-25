#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_dad);
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

TEST_CASE(dad_b) {
  write8(0, 0x09); // DAD B
  cpu->B = 0x00; cpu->C = 0x05; // BC contains 5
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3

  step_cpu();

  ASSERT_EQUAL(cpu->B, 0x00);
  ASSERT_EQUAL(cpu->C, 0x02);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dad_d) {
  write8(0, 0x19); // DAD D
  cpu->D = 0x00; cpu->E = 0x05; // DE contains 5
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3

  step_cpu();

  ASSERT_EQUAL(cpu->D, 0x00);
  ASSERT_EQUAL(cpu->E, 0x02);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dad_h) {
  write8(0, 0x29); // DAD H
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3

  step_cpu();

  ASSERT_EQUAL(cpu->H, 0xFF);
  ASSERT_EQUAL(cpu->L, 0xFA);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dad_sp) {
  write8(0, 0x39); // DAD SP
  cpu->SP = 0x05; // SP contains 5
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3

  step_cpu();

  ASSERT_EQUAL(cpu->SP, 0x0002);
  ASSERT_EQUAL(cpu->PC, 1);
}