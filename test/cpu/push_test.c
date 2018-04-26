#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_push);
BEFORE_EACH() {
  if (cpu == NULL) {
    create_cpu();
  }
  reset_cpu();

  if (memory == NULL) {
    create_memory(16);
  }

  // Zero out memory
  for (int i=0;i<16;i++) {
    write_byte(i, 0);
  }

  cpu->PC = 0;
  cpu->SP = 10;
}
AFTER_EACH() {}

TEST_CASE(push_b) {
  write_byte(0, 0xC5); // PUSH B
  cpu->B = 0xAB; cpu->C = 0xCD;

  step_cpu();

  ASSERT_EQUAL(pop_stack16(), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(push_d) {
  write_byte(0, 0xD5); // PUSH D
  cpu->D = 0xAB; cpu->E = 0xCD;

  step_cpu();

  ASSERT_EQUAL(pop_stack16(), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(push_h) {
  write_byte(0, 0xE5); // PUSH H
  cpu->H = 0xAB; cpu->L = 0xCD;

  step_cpu();

  ASSERT_EQUAL(pop_stack16(), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(push_psw) {
  write_byte(0, 0xF5); // PUSH PSW
  cpu->A = 0xAB;
  set_flag(FLAG_C, 1);
  set_flag(FLAG_P, 1);
  set_flag(FLAG_A, 1);
  set_flag(FLAG_Z, 1);
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(pop_stack16(), 0xABD7);
  ASSERT_EQUAL(cpu->PC, 1);
}
