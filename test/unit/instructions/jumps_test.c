#include "attounit.h"
#include "i8080.h"
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
  i8080_write_byte(cpu, 0, 0xC3); // JMP
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jmp_alternate_0xcb) {
  i8080_write_byte(cpu, 0, 0xCB); // JMP (alternate)
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(jnz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xC2); // JNZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jnz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xC2); // jnz
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xCA); // JZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(jz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xCA); // JZ
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jnc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xD2); // JNC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jnc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xD2); // JNC
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xDA); // JC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}


TEST_CASE(jc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xDA); // JC
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jpo_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xE2); // JPO
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jpo_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xE2); // JPO
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jpe_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xEA); // JPE
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jpe_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xEA); // JPE
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jp_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xF2); // JP
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jp_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xF2); // JP
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jm_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xFA); // JM
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(jm_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xFA); // JM
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(pchl) {
  i8080_write_byte(cpu, 0, 0xE9); // PCHL
  cpu->H = 0xAB; cpu->L = 0xCD;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 5);
}
