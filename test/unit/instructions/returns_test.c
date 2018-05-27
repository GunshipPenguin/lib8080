#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_ret);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
  i8080_push_stackw(cpu, 0xABCD);
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(ret) {
  i8080_write_byte(cpu, 0, 0xC9); // RET

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(ret_alternate_0xd9) {
  i8080_write_byte(cpu, 0, 0xD9); // RET (alternate)

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rnz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xC0); // RNZ
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rnz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xC0); // RNZ

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rz_z_flag_set) {
  i8080_write_byte(cpu, 0, 0xC8); // RZ
  i8080_set_flag(cpu, FLAG_Z, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rz_z_flag_unset) {
  i8080_write_byte(cpu, 0, 0xC8); // RZ

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rnc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xD0); // RNC
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rnc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xD0); // RNC

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rc_c_flag_set) {
  i8080_write_byte(cpu, 0, 0xD8); // RC
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rc_c_flag_unset) {
  i8080_write_byte(cpu, 0, 0xC8); // RZ

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rpo_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xE0); // RPO
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rpo_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xE0); // RPO

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rpe_p_flag_set) {
  i8080_write_byte(cpu, 0, 0xE8); // RPE
  i8080_set_flag(cpu, FLAG_P, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}


TEST_CASE(rpe_p_flag_unset) {
  i8080_write_byte(cpu, 0, 0xE8); // RPE

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rp_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xF0); // RP
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(rp_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xF0); // RP

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rm_s_flag_set) {
  i8080_write_byte(cpu, 0, 0xF8); // RM
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 0xABCD);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(rm_s_flag_unset) {
  i8080_write_byte(cpu, 0, 0xF8); // RM

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}
