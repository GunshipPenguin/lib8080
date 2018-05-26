#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_calls);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(call) {
  write_byte(cpu, 0, 0xCD); // CALL
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xdd) {
  write_byte(cpu, 0, 0xDD); // CALL (alternate)
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xed) {
  write_byte(cpu, 0, 0xED); // CALL (alternate)
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xfd) {
  write_byte(cpu, 0, 0xFD); // CALL (alternate)
  write_word(cpu, 1, 0xABCD); // a16

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}


TEST_CASE(cz_z_flag_set) {
  write_byte(cpu, 0, 0xCC); // CZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cz_z_flag_unset) {
  write_byte(cpu, 0, 0xCC); // CZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnz_z_flag_set) {
  write_byte(cpu, 0, 0xC4); // CNZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnz_z_flag_unset) {
  write_byte(cpu, 0, 0xC4); // CNZ
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cnc_c_flag_set) {
  write_byte(cpu, 0, 0xD4); // CNC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnc_c_flag_unset) {
  write_byte(cpu, 0, 0xD4); // CNC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cc_c_flag_set) {
  write_byte(cpu, 0, 0xDC); // CC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cc_c_flag_unset) {
  write_byte(cpu, 0, 0xDC); // CC
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cpo_p_flag_set) {
  write_byte(cpu, 0, 0xE4); // CPO
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cpo_p_flag_unset) {
  write_byte(cpu, 0, 0xE4); // CPO
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cpe_p_flag_set) {
  write_byte(cpu, 0, 0xEC); // CPE
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cpe_p_flag_unset) {
  write_byte(cpu, 0, 0xEC); // CPE
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cp_s_flag_set) {
  write_byte(cpu, 0, 0xF4); // CP
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cp_s_flag_unset) {
  write_byte(cpu, 0, 0xF4); // CP
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cm_s_flag_set) {
  write_byte(cpu, 0, 0xFC); // CM
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 1);

  step_cpu(cpu);


  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(pop_stackw(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cm_s_flag_unset) {
  write_byte(cpu, 0, 0xFC); // CM
  write_word(cpu, 1, 0xABCD); // a16
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}
