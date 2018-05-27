#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(register_pair_instructions)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(push_b) {
  i8080_write_byte(cpu, 0, 0xC5); // PUSH B
  cpu->B = 0xAB; cpu->C = 0xCD;

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(push_d) {
  i8080_write_byte(cpu, 0, 0xD5); // PUSH D
  cpu->D = 0xAB; cpu->E = 0xCD;

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(push_h) {
  i8080_write_byte(cpu, 0, 0xE5); // PUSH H
  cpu->H = 0xAB; cpu->L = 0xCD;

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 11);
}

TEST_CASE(push_psw) {
  i8080_write_byte(cpu, 0, 0xF5); // PUSH PSW
  cpu->A = 0xAB;
  i8080_set_flag(cpu, FLAG_C, 1);
  i8080_set_flag(cpu, FLAG_P, 1);
  i8080_set_flag(cpu, FLAG_A, 1);
  i8080_set_flag(cpu, FLAG_Z, 1);
  i8080_set_flag(cpu, FLAG_S, 1);

  i8080_step(cpu);

  ASSERT_EQUAL(i8080_pop_stackb(cpu), 0xABD7);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 11);
}


TEST_CASE(pop_b) {
  i8080_write_byte(cpu, 0, 0xC1); // POP B
  cpu->B = 0x00; cpu->C = 0x00;
  i8080_push_stackw(cpu, (0xABCD));

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->B, 0xAB);
  ASSERT_EQUAL(cpu->C, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(pop_d) {
  i8080_write_byte(cpu, 0, 0xD1); // POP D
  cpu->D = 0x00; cpu->E = 0x00;
  i8080_push_stackw(cpu, (0xABCD));

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 0xAB);
  ASSERT_EQUAL(cpu->E, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(pop_h) {
  i8080_write_byte(cpu, 0, 0xE1); // POP H
  cpu->H = 0x00; cpu->L = 0x00;
  i8080_push_stackw(cpu, (0xABCD));

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(pop_psw) {
  i8080_write_byte(cpu, 0, 0xF1); // POP PSW
  cpu->A = 0x00; cpu->flags = 2;
  i8080_push_stackw(cpu, (0xABD7));

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0xAB);
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_A));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(push_pop_psw) {
  i8080_write_byte(cpu, 0, 0xF5); // PUSH PSW
  i8080_write_byte(cpu, 1, 0xF1); // POP PSW
  cpu->A = 0xAB; cpu->flags = 0xD7;

  i8080_step(cpu);

  cpu->A = 0x00; cpu->flags = 0x02;
  i8080_step(cpu);

  ASSERT_EQUAL(cpu->PC, 2);
  ASSERT_EQUAL(cpu->flags, 0xD7);
  ASSERT_EQUAL(cpu->A, 0xAB);
}

TEST_CASE(dad_b) {
  i8080_write_byte(cpu, 0, 0x09); // DAD B
  cpu->B = 0xFF; cpu->C = 0xFD; // BC contains -3
  cpu->H = 0x00; cpu->L = 0x05; // HL contains 5

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0x00);
  ASSERT_EQUAL(cpu->L, 0x02);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(dad_d) {
  i8080_write_byte(cpu, 0, 0x19); // DAD D
  cpu->D = 0xFF; cpu->E = 0xFD; // DE contains -3
  cpu->H = 0x00; cpu->L = 0x05; // HL contains 5

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0x00);
  ASSERT_EQUAL(cpu->L, 0x02);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(dad_h) {
  i8080_write_byte(cpu, 0, 0x29); // DAD H
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0xFF);
  ASSERT_EQUAL(cpu->L, 0xFA);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

TEST_CASE(dad_sp) {
  i8080_write_byte(cpu, 0, 0x39); // DAD SP
  cpu->SP = 0xFFFD; // SP contains -3
  cpu->H = 0x00; cpu->L = 0x05; // HL contains 5

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0x00);
  ASSERT_EQUAL(cpu->L, 0x02);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 10);
}

// Bit flag tests
TEST_CASE(dad_sets_c_flag) {
  i8080_write_byte(cpu, 0, 0x19); // DAD D
  cpu->D = 0x00; cpu->E = 0x05; // DE contains 5
  cpu->H = 0xFF; cpu->L = 0xFD; // HL contains -3
  i8080_set_flag(cpu, FLAG_C, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(dad_resets_c_flag) {
  i8080_write_byte(cpu, 0, 0x19); // DAD D
  cpu->D = 0x00; cpu->E = 0x05; // DE contains 5
  cpu->H = 0x00; cpu->L = 0x01; // HL contains 1
  i8080_set_flag(cpu, FLAG_C, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 1);
}

TEST_CASE(inx_b) {
  i8080_write_byte(cpu, 0, 0x03); // INX B
  cpu->B = 0x00; cpu->C = 0xFF;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->B, 0x01);
  ASSERT_EQUAL(cpu->C, 0x00);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inx_d) {
  i8080_write_byte(cpu, 0, 0x13); // INX D
  cpu->D = 0x00; cpu->E = 0xFF;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 0x01);
  ASSERT_EQUAL(cpu->E, 0x00);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inx_h) {
  i8080_write_byte(cpu, 0, 0x23); // INX H
  cpu->H = 0x00; cpu->L = 0xFF;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0x01);
  ASSERT_EQUAL(cpu->L, 0x00);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(inx_sp) {
  i8080_write_byte(cpu, 0, 0x33); // INX SP
  cpu->SP = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->SP, 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}


TEST_CASE(dcx_b) {
  i8080_write_byte(cpu, 0, 0x0B); // DCX B
  cpu->B = 0x01; cpu->C = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->B, 0x00);
  ASSERT_EQUAL(cpu->C, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcx_d) {
  i8080_write_byte(cpu, 0, 0x1B); // DCX D
  cpu->D = 0x01; cpu->E = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 0x00);
  ASSERT_EQUAL(cpu->E, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcx_h) {
  i8080_write_byte(cpu, 0, 0x2B); // DCX H
  cpu->H = 0x01; cpu->L = 0x00;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->H, 0x00);
  ASSERT_EQUAL(cpu->L, 0xFF);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(dcx_sp) {
  i8080_write_byte(cpu, 0, 0x3B); // DCX SP
  cpu->SP = 0x01;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->SP, 0);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(xchg) {
  i8080_write_byte(cpu, 0, 0xEB); // XCHG
  cpu->H = 1; cpu->L = 2;
  cpu->D = 3; cpu->E = 4;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->E, 2);
  ASSERT_EQUAL(cpu->H, 3);
  ASSERT_EQUAL(cpu->L, 4);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}

TEST_CASE(xthl) {
  i8080_write_byte(cpu, 0, 0xE3); // XTHL

  cpu->SP = 10;
  i8080_write_byte(cpu, 10, 0xAB);
  i8080_write_byte(cpu, 11, 0xCD);
  cpu->H = 0x01; cpu->L = 0x02;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->L, 0xAB);
  ASSERT_EQUAL(cpu->H, 0xCD);
  ASSERT_EQUAL(i8080_read_byte(cpu, 10), 0x02);
  ASSERT_EQUAL(i8080_read_byte(cpu, 11), 0x01);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 18);
}

TEST_CASE(sphl) {
  i8080_write_byte(cpu, 0, 0xF9); // SPHL
  cpu->H = 0xAB; cpu->L = 0xCD;
  cpu->SP = 0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 5);
}
