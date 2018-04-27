#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_add);
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

// Individual opcode tests
TEST_CASE(add_b) {
  write_byte(0, 0x80);
  cpu->B = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_c) {
  write_byte(0, 0x81);
  cpu->C = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_d) {
  write_byte(0, 0x82);
  cpu->D = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_e) {
  write_byte(0, 0x83);
  cpu->E = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_h) {
  write_byte(0, 0x84);
  cpu->H = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_l) {
  write_byte(0, 0x85);
  cpu->L = 1; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_m) {
  write_byte(0, 0x86);
  write_byte(8, 1);
  cpu->L = 0x08; cpu->H = 0x00; cpu->A = 0;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(add_a) {
  write_byte(0, 0x87);
  cpu->A = 1;

  step_cpu();

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 1);
}

// Flag bit tests
TEST_CASE(add_sets_z_flag) {
  write_byte(0, 0x80); // ADD B
  cpu->A = 0x00; cpu->B = 0x00;
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_Z), 1);
}

TEST_CASE(add_sets_p_flag) {
  write_byte(0, 0x80); // ADD B
  cpu->A = 0x02; cpu->B = 0x01;
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_P), 1);
}

TEST_CASE(add_sets_s_flag) {
  write_byte(0, 0x80); // ADD B
  cpu->A = 0x7F; cpu->B = 0x01;
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_S), 1);
}

TEST_CASE(add_sets_a_flag) {
  write_byte(0, 0x80); // ADD B
  cpu->A = 0x0F; cpu->B = 0x01;
  set_flag(FLAG_A, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_A), 1);
}

TEST_CASE(add_sets_c_flag) {
  write_byte(0, 0x80); // ADD B
  cpu->A = 0xFF; cpu->B = 0x01;
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(get_flag(FLAG_C), 1);
}