#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_jumps);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(jmp) {
  write_byte(cpu, 0, 0xC3); // JMP
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jmp_alternate_0xcb) {
  write_byte(cpu, 0, 0xCB); // JMP (alternate)
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jnz_z_flag_set) {
  write_byte(cpu, 0, 0xC2); // JNZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnz_z_flag_unset) {
  write_byte(cpu, 0, 0xC2); // jnz
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jz_z_flag_set) {
  write_byte(cpu, 0, 0xCA); // JZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jz_z_flag_unset) {
  write_byte(cpu, 0, 0xCA); // JZ
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnc_c_flag_set) {
  write_byte(cpu, 0, 0xD2); // JNC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jnc_c_flag_unset) {
  write_byte(cpu, 0, 0xD2); // JNC
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jc_c_flag_set) {
  write_byte(cpu, 0, 0xDA); // JC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}


TEST_CASE(jc_c_flag_unset) {
  write_byte(cpu, 0, 0xDA); // JC
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jpo_p_flag_set) {
  write_byte(cpu, 0, 0xE2); // JPO
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jpo_p_flag_unset) {
  write_byte(cpu, 0, 0xE2); // JPO
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jpe_p_flag_set) {
  write_byte(cpu, 0, 0xEA); // JPE
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jpe_p_flag_unset) {
  write_byte(cpu, 0, 0xEA); // JPE
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jp_s_flag_set) {
  write_byte(cpu, 0, 0xF2); // JP
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(jp_s_flag_unset) {
  write_byte(cpu, 0, 0xF2); // JP
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jm_s_flag_set) {
  write_byte(cpu, 0, 0xFA); // JM
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}

TEST_CASE(jm_s_flag_unset) {
  write_byte(cpu, 0, 0xFA); // JM
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(pchl) {
  write_byte(cpu, 0, 0xE9); // PCHL
  cpu->H = 0xAB; cpu->L = 0xCD;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
}
