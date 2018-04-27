#include "attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_jumps);
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

TEST_CASE(jmp) {
  write_byte(0, 0xC3); // JMP
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jmp_alternate_0xcb) {
  write_byte(0, 0xCB); // JMP (alternate)
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jnz_z_flag_set) {
  write_byte(0, 0xC2); // JNZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnz_z_flag_unset) {
  write_byte(0, 0xC2); // jnz
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jz_z_flag_set) {
  write_byte(0, 0xCA); // JZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jz_z_flag_unset) {
  write_byte(0, 0xCA); // JZ
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnc_c_flag_set) {
  write_byte(0, 0xD2); // JNC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnc_c_flag_unset) {
  write_byte(0, 0xD2); // JNC
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jc_c_flag_set) {
  write_byte(0, 0xDA); // JC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jc_c_flag_unset) {
  write_byte(0, 0xDA); // JC
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jpo_p_flag_set) {
  write_byte(0, 0xE2); // JPO
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jpo_p_flag_unset) {
  write_byte(0, 0xE2); // JPO
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jpe_p_flag_set) {
  write_byte(0, 0xEA); // JPE
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jpe_p_flag_unset) {
  write_byte(0, 0xEA); // JPE
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jp_s_flag_set) {
  write_byte(0, 0xF2); // JP
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jp_s_flag_unset) {
  write_byte(0, 0xF2); // JP
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jm_s_flag_set) {
  write_byte(0, 0xFA); // JM
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jm_s_flag_unset) {
  write_byte(0, 0xFA); // JM
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}
