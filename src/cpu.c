#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"

struct cpu *cpu = NULL;

void create_cpu() {
  cpu = malloc(sizeof(struct cpu));
  cpu->PC = 0;
}

void reset_cpu() {
  cpu->A = 0;
  cpu->B = 0;
  cpu->C = 0;
  cpu->D = 0;
  cpu->E = 0;
  cpu->H = 0;
  cpu->L = 0;
  cpu->PC = 0;
  cpu->flags = 2;
  cpu->SP = 0;
}

int get_flag_mask(enum Flag flag) {
  switch (flag) {
    case FLAG_S: return 0x80;
    case FLAG_Z: return 0x40;
    case FLAG_A: return 0x10;
    case FLAG_P: return 0x04;
    case FLAG_C: return 0x01;
    default:
      fprintf(stderr, "Invalid flag %d", flag);
      exit(1);
  }
}
void set_flag(enum Flag flag, int val) {
  int mask = get_flag_mask(flag);

  if (val) {
    cpu->flags = (cpu->flags | mask) & 0xFF;
  } else {
    cpu->flags = (cpu->flags & ~mask) & 0xFF;
  }
}

int get_flag(enum Flag flag) {
  int mask = get_flag_mask(flag);
  return (cpu->flags & mask) != 0;
}

void set_reg(int reg, int val) {
  val &= 0xFF;

  switch (reg) {
    case 7: cpu->A = val;
      break;
    case 0: cpu->B = val;
      break;
    case 1: cpu->C = val;
      break;
    case 2: cpu->D = val;
      break;
    case 3: cpu->E = val;
      break;
    case 4: cpu->H = val;
      break;
    case 5: cpu->L = val;
      break;
    case 6: write_byte(CONCAT(cpu->H, cpu->L), val);
      break;
    default:
      fprintf(stderr, "Invalid register %d\n", reg);
      exit(1);
  }
}

int get_reg(int reg) {
  switch (reg) {
    case 7: return cpu->A;
    case 0: return cpu->B;
    case 1: return cpu->C;
    case 2: return cpu->D;
    case 3: return cpu->E;
    case 4: return cpu->H;
    case 5: return cpu->L;
    case 6: return read_byte(CONCAT(cpu->H, cpu->L));
    default:
      fprintf(stderr, "Invalid register %d\n", reg);
      exit(1);
  }
}

int get_reg_pair(int reg_pair) {
  switch (reg_pair) {
    case 0: return CONCAT(cpu->B, cpu->C);
    case 1: return CONCAT(cpu->D, cpu->E);
    case 2: return CONCAT(cpu->H, cpu->L);
    case 3: return cpu->SP;
    default:
      fprintf(stderr, "Invalid register pair %d\n", reg_pair);
      exit(1);
  }
}

void set_reg_pair(int reg_pair, int val) {
  int hi = (val >> 8) & 0xFF;
  int lo = val & 0xFF;

  switch (reg_pair) {
    case 0:
      cpu->B = hi;
      cpu->C = lo;
      break;
    case 1:
      cpu->D = hi;
      cpu->E = lo;
      break;
    case 2:
      cpu->H = hi;
      cpu->L = lo;
      break;
    case 3:
      cpu->SP = CONCAT(hi, lo);
      break;
    default:
      fprintf(stderr, "Invalid register pair %d\n", reg_pair);
      exit(1);
  }
}

// Sets the sign, zero and parity bits based on the given value
void setSZP(int val) {
  val &= 0xFF;

  set_flag(FLAG_S, val & 0x80);
  set_flag(FLAG_Z, val == 0);
  set_flag(FLAG_P, !__builtin_parity(val));
}

void push_stackb(int val) {
  write_byte(--cpu->SP, val & 0xFF);
}

void push_stackw(int val) {
  push_stackb((val & 0xFF00) >> 8);
  push_stackb(val & 0xFF);
}

int pop_stackb() {
  return read_byte(cpu->SP++);
}

int pop_stackw() {
  int lo = pop_stackb();
  int hi = pop_stackb();

  return CONCAT(hi, lo);
}

int next_byte() {
  return read_byte(cpu->PC++);
}

int next_word() {
  int word  = read_word(cpu->PC);
  cpu->PC += 2;
  return word;
}

// Instructions follow
// HLT - Halt
void hlt() {

}

// NOP - No Operation
void nop() {

}

// MOV - Move
void mov(int opcode) {
  int dst = (opcode & 0x38) >> 3;
  int src = opcode & 0x07;

  set_reg(dst, get_reg(src));
}

// MVI - Move Immediate
void mvi(int opcode) {
  int reg = (opcode & 0x38) >> 3;
  set_reg(reg, next_byte());
}

// STA - Store Accumulator Direct
void sta() {
  write_byte(next_word(), cpu->A);
}

// LDA - Load Accumulator Direct
void lda() {
  cpu->A = read_byte(next_word());
}

// LXI - Load Register Pair Immediate
void lxi(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;
  set_reg_pair(reg_pair, next_word());
}

// STAX - Store Accumulator
void stax(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;
  write_byte(get_reg_pair(reg_pair), cpu->A);
}

// LDAX - Load Accumulator
void ldax(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;
  cpu->A = read_byte(get_reg_pair(reg_pair));
}

// INR - Increment Register or Memory
void inr(int opcode) {
  int reg = (opcode & 0x38) >> 3;

  set_flag(FLAG_A, (get_reg(reg) & 0x0F) == 0x0F);
  set_reg(reg, get_reg(reg)+1);
  setSZP(get_reg(reg));
}

// DCR - Decrement Register or Memory
void dcr(int opcode) {
  int reg = (opcode & 0x38) >> 3;

  set_flag(FLAG_A, (get_reg(reg) & 0x0F) == 0);
  set_reg(reg, get_reg(reg)-1);
  setSZP(get_reg(reg));
}

// INX - Increment Register Pair
void inx(int opcode) {
  int reg = (opcode & 0x30) >> 4;
  set_reg_pair(reg, get_reg_pair(reg)+1);
}

// DCX - Decrement Register Pair
void dcx(int opcode) {
  int reg = (opcode & 0x30) >> 4;
  set_reg_pair(reg, get_reg_pair(reg)-1);
}

// ADD - Add Register or Memory to Accumulator
void add(int opcode) {
  int reg = opcode & 0x07;

  // Detect carry out of lower 4 bits
  set_flag(FLAG_A, ((cpu->A & 0xF) + (get_reg(reg) & 0x0F)) & 0x10);

  cpu->A += get_reg(reg);

  set_flag(FLAG_C, cpu->A & 0x100);
  cpu->A &= 0xFF;
  setSZP(cpu->A);
}

// SUB - Subtract Register or Memory from Accumulator
void sub(int opcode) {
  int reg = opcode & 0x07;
  set_flag(FLAG_C, get_reg(reg) > cpu->A);
  set_flag(FLAG_A, (cpu->A & 0x0F) < get_reg(reg));

  cpu->A -= get_reg(reg);
  cpu->A &= 0xFF;

  setSZP(cpu->A);
}

// ANA - Logical and Memory or Register with Accumulator
void ana(int opcode) {
  int reg = opcode & 0x07;
  cpu->A &= get_reg(reg);

  set_flag(FLAG_C, 0);
  setSZP(cpu->A);
}

// XRA - Logical Exclusive-Or Register or Memory With Accumulator
void xra(int opcode) {
  int reg = opcode & 0x07;
  cpu->A ^= get_reg(reg);

  set_flag(FLAG_C, 0);
  set_flag(FLAG_A, 0);
  setSZP(cpu->A);
}

// CMP - Compare Memory or Register With Accumulator
void cmp(int opcode) {
  int reg = opcode & 0x07;
  int res = cpu->A - get_reg(reg);

  set_flag(FLAG_C, get_reg(reg) > cpu->A);
  set_flag(FLAG_A, (cpu->A & 0x0F) < get_reg(reg));
  setSZP(res);
}

// ORA - Logical or Memory or Register with Accumulator
void ora(int opcode) {
  int reg = (opcode & 0x07);
  cpu->A |= get_reg(reg);

  set_flag(FLAG_C, 0);
  setSZP(cpu->A);
}

// RLC - Rotate Accumulator Left
void rlc() {
  int hi_bit = (cpu->A & 0x80) != 0;

  cpu->A <<= 1;
  cpu->A |= hi_bit;

  cpu->A &= 0xFF;

  set_flag(FLAG_C, hi_bit);
}

// RRC - Rotate Accumulator Right
void rrc() {
  int lo_bit = cpu->A & 0x01;

  cpu->A >>= 1;
  cpu->A |= (lo_bit << 7);
  cpu->A &= 0xFF;

  set_flag(FLAG_C, lo_bit);
}

// RAL - Rotate Accumulator Left Through Carry
void ral() {
  int old_carry = get_flag(FLAG_C);

  set_flag(FLAG_C, cpu->A & 0x80);
  cpu->A <<= 1;
  cpu->A &= 0xFF;

  cpu->A |= old_carry & 0x01;
}

// RAR - Rotate Accumulator Right Through Carry
void rar() {
  int old_carry = get_flag(FLAG_C);

  set_flag(FLAG_C, cpu->A & 0x01);
  cpu->A >>= 1;
  cpu->A &= 0xFF;

  cpu->A |= ((old_carry << 7) & 0x80);
}

// CMC - Complement Carry Bit
void cmc() {
  set_flag(FLAG_C, !get_flag(FLAG_C));
}

// CMA - Complement Accumulator
void cma() {
  cpu->A = (~cpu->A) & 0xFF;
}

// STC - Set Carry Bit
void stc() {
  set_flag(FLAG_C, 1);
}

// DAD - Double Add
void dad(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;

  int new_val = (CONCAT(cpu->H, cpu->L) + get_reg_pair(reg_pair));
  set_flag(FLAG_C, new_val & 0x10000);
  new_val &= 0xFFFF;

  set_reg_pair(reg_pair, new_val);
}

// XCHG - Exchange Registers
void xchg() {
  int h_temp = cpu->H;
  int l_temp = cpu->L;

  cpu->H = cpu->D;
  cpu->L = cpu->E;
  cpu->D = h_temp;
  cpu->E = l_temp;
}

// SPHL - Load SP from H and L
void sphl() {
  cpu->SP = CONCAT(cpu->H, cpu->L);
}

// SHLD - Store H and L direct
void shld() {
  int addr = next_word();
  write_byte(addr, cpu->L);
  write_byte(addr + 1, cpu->H);
}

// LDHD - Load H and L direct
void ldhd() {
  int addr = next_word();
  cpu->L = read_byte(addr);
  cpu->H = read_byte(addr + 1);
}

// PUSH - Push Data Onto Stack
void push(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;

  // Register pair 3 refers to the concatenation of A and flags with push/pop
  int data = reg_pair == 3 ? CONCAT(cpu->A, cpu->flags) : get_reg_pair(reg_pair);
  push_stackw(data);
}

// POP - Pop Data From Stack
void pop(int opcode) {
  int reg_pair = (opcode & 0x30) >> 4;

  if (reg_pair == 3) { // PSW special case for push/pop
    cpu->A = pop_stackb();
    cpu->flags = pop_stackb();
  } else {
    set_reg_pair(reg_pair, pop_stackw());
  }
}

// Call - Call
void call() {
  push_stackw(cpu->PC+2);
  cpu->PC = next_word();
}

// CC - Call if Carry
void cc() {
  if (get_flag(FLAG_C)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CNC - Call if no Carry
void cnc() {
  if (!get_flag(FLAG_C)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CZ - Call if Zero
void cz() {
  if (get_flag(FLAG_Z)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CNZ - Call if not Zero
void cnz() {
  if (!get_flag(FLAG_Z)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CM - Call if Minus
void cm() {
  if (get_flag(FLAG_S)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CP - Call if Plus
void cp() {
  if (!get_flag(FLAG_S)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CPE - Call if Parity Even
void cpe() {
  if (get_flag(FLAG_P)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// CPO - Call if Parity Odd
void cpo() {
  if (!get_flag(FLAG_P)) {
    push_stackw(cpu->PC+2);
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// RET - Return
void ret() {
  cpu->PC = pop_stackw();
}

// RNZ - Return if not Zero
void rnz() {
  if (!get_flag(FLAG_Z)) {
    cpu->PC = pop_stackw();
  }
}

// RZ - Return if Zero
void rz() {
  if (get_flag(FLAG_Z)) {
    cpu->PC = pop_stackw();
  }
}

// RNC - Return if no Carry
void rnc() {
  if (!get_flag(FLAG_C)) {
    cpu->PC = pop_stackw();
  }
}

// RC - Return if Carry
void rc() {
  if (get_flag(FLAG_C)) {
    cpu->PC = pop_stackw();
  }
}

// RPO - Return if Parity Odd
void rpo() {
  if (!get_flag(FLAG_P)) {
    cpu->PC = pop_stackw();
  }
}

// RPE - Return if Parity Even
void rpe() {
  if (get_flag(FLAG_P)) {
    cpu->PC = pop_stackw();
  }
}

// RP - Return if Positive
void rp() {
  if (!get_flag(FLAG_S)) {
    cpu->PC = pop_stackw();
  }
}

// RM - Return if Minus
void rm() {
  if (get_flag(FLAG_S)) {
    cpu->PC = pop_stackw();
  }
}

// JMP - Jump
void jmp() {
  cpu->PC = next_word();
}

// JNZ - Jump if not Zero
void jnz() {
  if (!get_flag(FLAG_Z)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JZ - Jump if Zero
void jz() {
  if (get_flag(FLAG_Z)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JNC - Jump if no Carry
void jnc() {
  if (!get_flag(FLAG_C)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JC - Jump if Carry
void jc() {
  if (get_flag(FLAG_C)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JPO - Jump if Parity Odd
void jpo() {
  if (!get_flag(FLAG_P)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JPE - Jump if Parity Even
void jpe() {
  if (get_flag(FLAG_P)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JP - Jump if Plus
void jp() {
  if (!get_flag(FLAG_S)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

// JM - Jump if Minus
void jm() {
  if (get_flag(FLAG_S)) {
    cpu->PC = next_word();
  } else {
    cpu->PC += 2;
  }
}

void step_cpu() {
  int opcode = next_byte();

  switch (opcode) {
    case 0x00: // NOP
    case 0x08: // NOP (alternate)
    case 0x10: // NOP (alternate)
    case 0x18: // NOP (alternate)
    case 0x20: // NOP (alternate)
    case 0x28: // NOP (alternate)
    case 0x30: // NOP (alternate)
    case 0x38: // NOP (alternate)
      nop();
      break;

    case 0x22: // SHLD a16
      shld();
      break;

    case 0x2A: // LDHD a16
      ldhd();
      break;

    case 0x2F: // CMA
      cma();
      break;

    case 0x3F: // CMC
      cmc();
      break;

    case 0x01: // LXI B, d16
    case 0x11: // LXI D, d16
    case 0x21: // LXI H, d16
    case 0x31: // LXI SP, d16
      lxi(opcode);
      break;

    case 0x09: // DAD B
    case 0x19: // DAD D
    case 0x29: // DAD H
    case 0x39: // DAD SP
      dad(opcode);
      break;

    case 0x37: // STC
      stc();
      break;

    case 0x02: // STAX B
    case 0x12: // STAX D
      stax(opcode);
      break;

    case 0x0A: // LDAX B
    case 0x1A: // LDAX D
      ldax(opcode);
      break;

    case 0x07: // RLC
      rlc();
      break;

    case 0x0F: // RRC
      rrc();
      break;

    case 0x17: // RAL
      ral();
      break;

    case 0x1F: // RAR
      rar();
      break;

    case 0x03: // INX B
    case 0x13: // INX D
    case 0x23: // INX H
    case 0x33: // INX SP
      inx(opcode);
      break;

    case 0x0B: // DCX B
    case 0x1B: // DCX D
    case 0x2B: // DCX H
    case 0x3B: // DCX SP
      dcx(opcode);
      break;

    case 0x04: // INR B
    case 0x0C: // INR C
    case 0x14: // INR D
    case 0x1C: // INR E
    case 0x24: // INR H
    case 0x2C: // INR L
    case 0x34: // INR M
    case 0x3C: // INR A
      inr(opcode);
      break;

    case 0x05: // DCR B
    case 0x0D: // DCR C
    case 0x15: // DCR D
    case 0x1D: // DCR E
    case 0x25: // DCR H
    case 0x2D: // DCR L
    case 0x35: // DCR M
    case 0x3D: // DCR A
      dcr(opcode);
      break;

    case 0x06: // MVI B, d8
    case 0x0E: // MVI C, d8
    case 0x16: // MVI D, d8
    case 0x1E: // MVI E, d8
    case 0x2E: // MVI L, d8
    case 0x3E: // MVI A, d8
    case 0x26: // MVI H, d8
    case 0x36: // MVI M, d8
      mvi(opcode);
      break;

    case 0x32: // STA a16
      sta();
      break;

    case 0x3A: // LDA a16
      lda();
      break;

    case 0x40: // MOV B, B
    case 0x41: // MOV B, C
    case 0x42: // MOV B, D
    case 0x43: // MOV B, E
    case 0x44: // MOV B, E
    case 0x45: // MOV B, H
    case 0x46: // MOV B, L
    case 0x47: // MOV B, M
    case 0x48: // MOV B, A
    case 0x49: // MOV C, B
    case 0x4A: // MOV C, C
    case 0x4B: // MOV C, D
    case 0x4C: // MOV C, E
    case 0x4D: // MOV C, L
    case 0x4E: // MOV C, M
    case 0x4F: // MOV C, A
    case 0x50: // MOV D, B
    case 0x51: // MOV D, C
    case 0x52: // MOV D, D
    case 0x53: // MOV D, E
    case 0x54: // MOV D, H
    case 0x55: // MOV D, L
    case 0x56: // MOV D, M
    case 0x57: // MOV D, A
    case 0x58: // MOV E, B
    case 0x59: // MOV E, C
    case 0x5A: // MOV E, D
    case 0x5B: // MOV E, E
    case 0x5C: // MOV E, H
    case 0x5D: // MOV E, L
    case 0x5E: // MOV E, M
    case 0x5F: // MOV E, A
    case 0x60: // MOV H, B
    case 0x61: // MOV H, C
    case 0x62: // MOV H, D
    case 0x63: // MOV H, E
    case 0x64: // MOV H, H
    case 0x65: // MOV H, L
    case 0x66: // MOV H, M
    case 0x67: // MOV H, A
    case 0x68: // MOV L, B
    case 0x69: // MOV L, C
    case 0x6A: // MOV L, D
    case 0x6B: // MOV L, E
    case 0x6C: // MOV L, H
    case 0x6D: // MOV L, L
    case 0x6E: // MOV L, M
    case 0x6F: // MOV L, A
    case 0x70: // MOV M, B
    case 0x71: // MOV M, C
    case 0x72: // MOV M, D
    case 0x73: // MOV M, E
    case 0x74: // MOV M, H
    case 0x75: // MOV M, L
    case 0x77: // MOV M, A
    case 0x78: // MOV A, B
    case 0x79: // MOV A, C
    case 0x7A: // MOV A, D
    case 0x7B: // MOV A, E
    case 0x7C: // MOV A, H
    case 0x7D: // MOV A, L
    case 0x7E: // MOV A, M
    case 0x7F: // MOV A, A
      mov(opcode);
      break;

    case 0x76: // HLT
      hlt();
      break;

    case 0x80: // ADD B
    case 0x81: // ADD C
    case 0x82: // ADD D
    case 0x83: // ADD E
    case 0x84: // ADD H
    case 0x85: // ADD L
    case 0x86: // ADD M
    case 0x87: // ADD A
      add(opcode);
      break;

    case 0x90: // SUB B
    case 0x91: // SUB C
    case 0x92: // SUB D
    case 0x93: // SUB E
    case 0x94: // SUB H
    case 0x95: // SUB L
    case 0x96: // SUB M
    case 0x97: // SUB A
      sub(opcode);
      break;

    case 0xA0: // ANA B
    case 0xA1: // ANA C
    case 0xA2: // ANA D
    case 0xA3: // ANA E
    case 0xA4: // ANA H
    case 0xA5: // ANA L
    case 0xA6: // ANA M
    case 0xA7: // ANA A
      ana(opcode);
      break;

    case 0xA8: // XRA B
    case 0xA9: // XRA C
    case 0xAA: // XRA D
    case 0xAB: // XRA E
    case 0xAC: // XRA H
    case 0xAD: // XRA L
    case 0xAE: // XRA M
    case 0xAF: // XRA A
      xra(opcode);
      break;

    case 0xB0: // ORA B
    case 0xB1: // ORA C
    case 0xB2: // ORA D
    case 0xB3: // ORA E
    case 0xB4: // ORA H
    case 0xB5: // ORA L
    case 0xB6: // ORA M
    case 0xB7: // ORA A
      ora(opcode);
      break;

    case 0xB8: // CMP B
    case 0xB9: // CMP C
    case 0xBA: // CMP D
    case 0xBB: // CMP E
    case 0xBC: // CMP H
    case 0xBD: // CMP L
    case 0xBE: // CMP M
    case 0xBF: // CMP A
      cmp(opcode);
      break;

    case 0xC1: // POP B
    case 0xD1: // POP D
    case 0xE1: // POP H
    case 0xF1: // POP PSW
      pop(opcode);
      break;

    case 0xC5: // PUSH B
    case 0xD5: // PUSH D
    case 0xE5: // PUSH H
    case 0xF5: // PUSH PSW
      push(opcode);
      break;

    case 0xC3: // JMP a16
    case 0xCB: // JMP a16 (alternate)
      jmp();
      break;

    case 0xC2: // JNZ a16
      jnz();
      break;

    case 0xCA: // JZ a16
      jz();
      break;

    case 0xD2: // JNC a16
      jnc();
      break;

    case 0xDA: // JC a16
      jc();
      break;

    case 0xE2: // JPO a16
      jpo();
      break;

    case 0xEA: // JPE a16
      jpe();
      break;

    case 0xF2: // JP a16
      jp();
      break;

    case 0xFA: // JM a16
      jm();
      break;

    case 0xC0: // RNZ
      rnz();
      break;

    case 0xC8: // RZ
      rz();
      break;

    case 0xC9: // RET
    case 0xD9: // RET (alternate)
      ret();
      break;

    case 0xD0: // RNC
      rnc();
      break;

    case 0xD8: // RC
      rc();
      break;

    case 0xE0: // RPO
      rpo();
      break;

    case 0xE8: // RPE
      rpe();
      break;

    case 0xF0: // RP
      rp();
      break;

    case 0xF8: // RM
      rm();
      break;

    case 0xCD: // CALL a16
    case 0xDD: // CALL a16 (alternate)
    case 0xED: // CALL a16 (alternate)
    case 0xFD: // CALL a16 (alternate)
      call();
      break;

    case 0xC4: // CNZ a16
      cnz();
      break;

    case 0xCC: // CZ a16
      cz();
      break;

    case 0xD4: // CNC a16
      cnc();
      break;

    case 0xDC: // CC a16
      cc();
      break;

    case 0xE4: // CPO a16
      cpo();
      break;

    case 0xEC: // CPE a16
      cpe();
      break;

    case 0xF4: // CP a16
      cp();
      break;

    case 0xFC: // CM a16
      cm();
      break;

    case 0xEB: // XCHG
      xchg();
      break;

    case 0xF9: // SPHL
      sphl();
      break;

    default:
      fprintf(stderr, "Opcode not implemented 0x%x\n", opcode);
      exit(1);
  }
}