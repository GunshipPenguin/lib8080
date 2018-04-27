#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_ret);
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

  cpu->SP = 10;
  push_stackw(0xABCD);
}
AFTER_EACH() {}

TEST_CASE(ret) {
  write_byte(0, 0xC9); // RET

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(ret_alternate_0xd9) {
  write_byte(0, 0xD9); // RET (alternate)

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rnz_z_flag_set) {
  write_byte(0, 0xC0); // RNZ
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rnz_z_flag_unset) {
  write_byte(0, 0xC0); // RNZ

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rz_z_flag_set) {
  write_byte(0, 0xC8); // RZ
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rz_z_flag_unset) {
  write_byte(0, 0xC8); // RZ

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rnc_c_flag_set) {
  write_byte(0, 0xD0); // RNC
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rnc_c_flag_unset) {
  write_byte(0, 0xD0); // RNC

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rc_c_flag_set) {
  write_byte(0, 0xD8); // RC
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rc_c_flag_unset) {
  write_byte(0, 0xC8); // RZ

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rpo_p_flag_set) {
  write_byte(0, 0xE0); // RPO
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rpo_p_flag_unset) {
  write_byte(0, 0xE0); // RPO

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rpe_p_flag_set) {
  write_byte(0, 0xE8); // RPE
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(rpe_p_flag_unset) {
  write_byte(0, 0xE8); // RPE

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rp_s_flag_set) {
  write_byte(0, 0xF0); // RP
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(rp_s_flag_unset) {
  write_byte(0, 0xF0); // RP

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rm_s_flag_set) {
  write_byte(0, 0xF8); // RM
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(rm_s_flag_unset) {
  write_byte(0, 0xF8); // RM

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 1);
}
