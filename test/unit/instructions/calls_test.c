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
  i8080_write_byte(cpu, 0, 0xCD); // CALL
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xdd) {
  i8080_write_byte(cpu, 0, 0xDD); // CALL (alternate)
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xed) {
  i8080_write_byte(cpu, 0, 0xED); // CALL (alternate)
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(call_alternate_0xfd) {
  i8080_write_byte(cpu, 0, 0xFD); // CALL (alternate)
  i8080_write_word(cpu, 1, 0xABCD); // a16

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}


TEST_CASE(cz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xCC); // CZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xCC); // CZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xC4); // CNZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xC4); // CNZ
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cnc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xD4); // CNC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cnc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xD4); // CNC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xDC); // CC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xDC); // CC
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cpo_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xE4); // CPO
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cpo_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xE4); // CPO
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cpe_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xEC); // CPE
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cpe_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xEC); // CPE
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cp_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xF4); // CP
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(cp_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xF4); // CP
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cm_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xFC); // CM
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);


  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(i8080_pop_stackb(cpu), 3);
  ASSERT_EQUAL(cpu->cyc, 17);
}

TEST_CASE(cm_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xFC); // CM
  i8080_write_word(cpu, 1, 0xABCD); // a16
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 3);
  ASSERT_EQUAL(cpu->cyc, 11);
}
