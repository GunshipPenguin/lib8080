#include "unit/attounit.h"
#include "cpu.h"
#include "memory.h"

TEST_SUITE(instruction_calls);
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
}
AFTER_EACH() {}

TEST_CASE(call) {
  write_byte(0, 0xCD); // CALL
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(call_alternate_0xdd) {
  write_byte(0, 0xDD); // CALL (alternate)
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(call_alternate_0xed) {
  write_byte(0, 0xED); // CALL (alternate)
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(call_alternate_0xfd) {
  write_byte(0, 0xFD); // CALL (alternate)
  write_word(1, 0xABCD); // a16

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}


TEST_CASE(cz_z_flag_set) {
  write_byte(0, 0xCC); // CZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cz_z_flag_unset) {
  write_byte(0, 0xCC); // CZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cnz_z_flag_set) {
  write_byte(0, 0xC4); // CNZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cnz_z_flag_unset) {
  write_byte(0, 0xC4); // CNZ
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_Z, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cnc_c_flag_set) {
  write_byte(0, 0xD4); // CNC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cnc_c_flag_unset) {
  write_byte(0, 0xD4); // CNC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cc_c_flag_set) {
  write_byte(0, 0xDC); // CC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cc_c_flag_unset) {
  write_byte(0, 0xDC); // CC
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_C, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cpo_p_flag_set) {
  write_byte(0, 0xE4); // CPO
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cpo_p_flag_unset) {
  write_byte(0, 0xE4); // CPO
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cpe_p_flag_set) {
  write_byte(0, 0xEC); // CPE
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cpe_p_flag_unset) {
  write_byte(0, 0xEC); // CPE
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_P, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cp_s_flag_set) {
  write_byte(0, 0xF4); // CP
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 1);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(cp_s_flag_unset) {
  write_byte(0, 0xF4); // CP
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cm_s_flag_set) {
  write_byte(0, 0xFC); // CM
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 1);

  step_cpu();


  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(), 3);
}

TEST_CASE(cm_s_flag_unset) {
  write_byte(0, 0xFC); // CM
  write_word(1, 0xABCD); // a16
  set_flag(FLAG_S, 0);

  step_cpu();

  ASSERT_EQUAL(cpu->PC, 3);
}
