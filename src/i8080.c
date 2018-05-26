#include <stdio.h>
#include <stdlib.h>
#include "i8080.h"

#define CONCAT(HI, LO) ((((HI) << 8) | ((LO) & 0XFF)) & 0XFFFF)

// External API
void reset_cpu(struct i8080 *cpu) {
  cpu->A = 0;
  cpu->B = 0;
  cpu->C = 0;
  cpu->D = 0;
  cpu->E = 0;
  cpu->H = 0;
  cpu->L = 0;
  cpu->PC = 0;
  cpu->INTE = 0;
  cpu->flags = 2;
  cpu->SP = 0;
  cpu->halted = 0;

  cpu->input_handler = NULL;
  cpu->output_handler = NULL;

  cpu->pending_interrupt = 0;
  cpu->interrupt_opcode = 0;
}

void request_interrupt(struct i8080 *cpu, uint opcode) {
  cpu->halted = 0;
  if (cpu->INTE) {
    cpu->INTE = 0;
    cpu->pending_interrupt = 1;
    cpu->interrupt_opcode = opcode;
  }
}

void load_memory(struct i8080 *cpu, char *path, size_t offset) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    perror("fopen");
    exit(1);
  }

  for (int i=0;i<cpu->memsize;i++) {
    size_t res = fread(cpu->memory+(offset+i), sizeof(char), 1, file);

    if (res == 0) break;
  };

  fclose(file);
}


// Internal logic
uint read_byte(struct i8080 *cpu, uint addr) {
  return cpu->memory[addr] & 0xFF;
}

uint read_word(struct i8080 *cpu, uint addr) {
  int hi = cpu->memory[addr+1] & 0xFF;
  int lo = cpu->memory[addr] & 0xFF;

  return (hi << 8) | lo;
}

void write_byte(struct i8080 *cpu, uint addr, uint data) {
  cpu->memory[addr] = (char) data;
}

void write_word(struct i8080 *cpu, uint addr, uint data) {
  char hi = (data >> 8) & 0xFF;
  char lo = data & 0xFF;

  cpu->memory[addr] = lo;
  cpu->memory[addr+1] = hi;
}

uint get_flag_mask(enum Flag flag) {
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

void set_flag(struct i8080 *cpu, enum Flag flag, int val) {
  uint mask = get_flag_mask(flag);

  if (val) {
    cpu->flags = (cpu->flags | mask) & 0xFF;
  } else {
    cpu->flags = (cpu->flags & ~mask) & 0xFF;
  }
}

int get_flag(struct i8080 *cpu, enum Flag flag) {
  uint mask = get_flag_mask(flag);
  return (cpu->flags & mask) != 0;
}

int check_condition(struct i8080 *cpu, uint condition) {
  switch (condition) {
    case 0: return !get_flag(cpu, FLAG_Z); // No zero
    case 1: return get_flag(cpu, FLAG_Z); // Zero
    case 2: return !get_flag(cpu, FLAG_C); // No carry
    case 3: return get_flag(cpu, FLAG_C); // Carry
    case 4: return !get_flag(cpu, FLAG_P); // Parity odd
    case 5: return get_flag(cpu, FLAG_P); // Parity even
    case 6: return !get_flag(cpu, FLAG_S); // Positive
    case 7: return get_flag(cpu, FLAG_S); // Negative
    default:
      fprintf(stderr, "Invalid condition code %d", condition);
      exit(1);
  }
}

void set_reg(struct i8080 *cpu, uint reg, uint val) {
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
    case 6: write_byte(cpu, CONCAT(cpu->H, cpu->L), val);
      break;
    default:
      fprintf(stderr, "Invalid register %d\n", reg);
      exit(1);
  }
}

uint get_reg(struct i8080 *cpu, uint reg) {
  switch (reg) {
    case 7: return cpu->A;
    case 0: return cpu->B;
    case 1: return cpu->C;
    case 2: return cpu->D;
    case 3: return cpu->E;
    case 4: return cpu->H;
    case 5: return cpu->L;
    case 6: return read_byte(cpu, CONCAT(cpu->H, cpu->L));
    default:
      fprintf(stderr, "Invalid register %d\n", reg);
      exit(1);
  }
}

uint get_reg_pair(struct i8080 *cpu, uint reg_pair) {
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

void set_reg_pair(struct i8080 *cpu, uint reg_pair, uint val) {
  uint hi = (val >> 8) & 0xFF;
  uint lo = val & 0xFF;

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
void setSZP(struct i8080 *cpu, uint val) {
  val &= 0xFF;

  set_flag(cpu, FLAG_S, val & 0x80);
  set_flag(cpu, FLAG_Z, val == 0);
  set_flag(cpu, FLAG_P, !__builtin_parity(val));
}

void push_stackb(struct i8080 *cpu, uint val) {
  cpu->SP = (cpu->SP-1) & 0XFFFF;
  write_byte(cpu, cpu->SP, val & 0xFF);
}

void push_stackw(struct i8080 *cpu, uint val) {
  push_stackb(cpu, (val & 0xFF00) >> 8);
  push_stackb(cpu, val & 0xFF);
}

uint pop_stackb(struct i8080 *cpu) {
  uint byte = read_byte(cpu, cpu->SP);
  cpu->SP = (cpu->SP + 1) & 0xFFFF;
  return byte;
}

uint pop_stackw(struct i8080 *cpu) {
  uint lo = pop_stackb(cpu);
  uint hi = pop_stackb(cpu);

  return CONCAT(hi, lo);
}

uint next_byte(struct i8080 *cpu) {
  return read_byte(cpu, cpu->PC++);
}

uint next_word(struct i8080 *cpu) {
  uint word  = read_word(cpu, cpu->PC);
  cpu->PC += 2;
  return word;
}

uint next_instruction_opcode(struct i8080 *cpu) {
  if (cpu->pending_interrupt) {
    return cpu->interrupt_opcode;
  } else {
    return next_byte(cpu);
  }
}

uint perform_sub(struct i8080 *cpu, uint minu, uint subt, int borrow) {
  uint subt_ones = (~subt) & 0xFF;

  // Minuend plus ones complement of subtrahend with a carry input
  // Note that if there is a borrow, we negate the carry in (for forming the
  // 2's complement) as the borrow will cancel it out
  uint res16 = minu + subt_ones + (borrow ? 0 : 1);
  uint res8 = res16 & 0xFF;

  set_flag(cpu, FLAG_C, !(res16 & 0x100));
  set_flag(cpu, FLAG_A, ((minu & 0xF) + (subt_ones & 0xF) + (borrow ? 0 : 1)) & 0x10);
  setSZP(cpu, res8);

  return res8;
}

uint perform_add(struct i8080 *cpu, uint a, uint b, int carry) {
  uint carry_val = carry ? 1 : 0;

  uint res16 = a + b + carry_val;
  uint res8 = res16 & 0xFF;

  set_flag(cpu, FLAG_C, res16 & 0x100);
  set_flag(cpu, FLAG_A, (((a & 0xF) + (b & 0xF) + carry_val) & 0x10));
  setSZP(cpu, res8);

  return res8;
}

// Instructions follow
// HLT - Halt
void hlt(struct i8080 *cpu) {
  cpu->halted = 1;
}

// NOP - No Operation
void nop(struct i8080 *cpu) {

}

// MOV - Move
void mov(struct i8080 *cpu, uint opcode) {
  uint  dst = (opcode & 0x38) >> 3;
  uint  src = opcode & 0x07;

  set_reg(cpu, dst, get_reg(cpu, src));
}

// MVI - Move Immediate
void mvi(struct i8080 *cpu, uint opcode) {
  uint reg = (opcode & 0x38) >> 3;
  set_reg(cpu, reg, next_byte(cpu));
}

// STA - Store Accumulator Direct
void sta(struct i8080 *cpu) {
  write_byte(cpu, next_word(cpu), cpu->A);
}

// LDA - Load Accumulator Direct
void lda(struct i8080 *cpu) {
  cpu->A = read_byte(cpu, next_word(cpu));
}

// LXI - Load Register Pair Immediate
void lxi(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;
  set_reg_pair(cpu, reg_pair, next_word(cpu));
}

// STAX - Store Accumulator
void stax(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;
  write_byte(cpu, get_reg_pair(cpu, reg_pair), cpu->A);
}

// LDAX - Load Accumulator
void ldax(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;
  cpu->A = read_byte(cpu, get_reg_pair(cpu, reg_pair));
}

// INR - Increment Register or Memory
void inr(struct i8080 *cpu, uint opcode) {
  uint reg = (opcode & 0x38) >> 3;

  set_flag(cpu, FLAG_A, (get_reg(cpu, reg) & 0x0F) == 0x0F);
  set_reg(cpu, reg, get_reg(cpu, reg)+1);
  setSZP(cpu, get_reg(cpu, reg));
}

// DCR - Decrement Register or Memory
void dcr(struct i8080 *cpu, uint opcode) {
  uint reg = (opcode & 0x38) >> 3;

  set_flag(cpu, FLAG_A, !(get_reg(cpu, reg) & 0x0F) == 0);
  set_reg(cpu, reg, get_reg(cpu, reg)-1);
  setSZP(cpu, get_reg(cpu, reg));
}

// INX - Increment Register Pair
void inx(struct i8080 *cpu, uint opcode) {
  uint reg = (opcode & 0x30) >> 4;
  set_reg_pair(cpu, reg, get_reg_pair(cpu, reg)+1);
}

// DCX - Decrement Register Pair
void dcx(struct i8080 *cpu, uint opcode) {
  uint reg = (opcode & 0x30) >> 4;
  set_reg_pair(cpu, reg, get_reg_pair(cpu, reg)-1);
}

// DAA - Decimal Adjust Accumulator
void daa(struct i8080 *cpu) {
  uint add = 0;

  if (((cpu->A & 0xF) > 9) || get_flag(cpu, FLAG_A)) {
    add |= 0x06;
  }

  int carry = get_flag(cpu, FLAG_C);
  /*
   * If the upper nibble is greater than 9
   * or the upper nibble will be greater than 9 when adding 6 to the lower nibble
   * or the carry flag is set
   */
  if (((cpu->A & 0xF0) > 0x90) ||
      (((cpu->A & 0xF0) >= 0x90) && ((cpu->A & 0xF) > 9)) ||
      get_flag(cpu, FLAG_C)) {
    add |= 0x60;
    carry = 1;
  }

  cpu->A = perform_add(cpu, cpu->A, add, 0);

  // The carry bit is unaffected if there is no carry out of the upper nibble
  set_flag(cpu, FLAG_C, carry);
}

// ADD - Add Register or Memory to Accumulator
void add(struct i8080 *cpu, uint opcode) {
  cpu->A = perform_add(cpu, cpu->A, get_reg(cpu, opcode & 0x7), 0);
}

// ADC - Add Register or Memory to Accumulator With Carry
void adc(struct i8080 *cpu, uint opcode) {
  cpu->A = perform_add(cpu, cpu->A, get_reg(cpu, opcode & 0x7), get_flag(cpu, FLAG_C));
}

// SBB - Subtract Register or Memory from Accumulator with Borrow
void sbb(struct i8080 *cpu, uint opcode) {
  cpu->A = perform_sub(cpu, cpu->A, get_reg(cpu, opcode & 0x7), get_flag(cpu, FLAG_C));
}

// SUB - Subtract Register or Memory from Accumulator
void sub(struct i8080 *cpu, uint opcode) {
  cpu->A = perform_sub(cpu, cpu->A, get_reg(cpu, opcode & 0x7), 0);
}

// ANA - Logical and Memory or Register with Accumulator
void ana(struct i8080 *cpu, uint opcode) {
  uint reg = opcode & 0x07;
  set_flag(cpu, FLAG_A, (get_reg(cpu, reg) | cpu->A) & 0x08);

  cpu->A &= get_reg(cpu, reg);

  set_flag(cpu, FLAG_C, 0);
  setSZP(cpu, cpu->A);
}

// XRA - Logical Exclusive-Or Register or Memory With Accumulator
void xra(struct i8080 *cpu, uint opcode) {
  uint reg = opcode & 0x07;
  cpu->A ^= get_reg(cpu, reg);

  set_flag(cpu, FLAG_C, 0);
  set_flag(cpu, FLAG_A, 0);
  setSZP(cpu, cpu->A);
}

// ADI - Add Immediate to Accumulator
void adi(struct i8080 *cpu) {
  cpu->A = perform_add(cpu, cpu->A, next_byte(cpu), 0);
}

// SUI - Subtract Immediate From Accumulator
void sui(struct i8080 *cpu) {
  cpu->A = perform_sub(cpu, cpu->A, next_byte(cpu), 0);
}

// ANI - Logical and Immediate With Accumulator
void ani(struct i8080 *cpu) {
  uint val = next_byte(cpu);
  set_flag(cpu, FLAG_A, (val | cpu->A) & 0x08);

  cpu->A &= val;

  set_flag(cpu, FLAG_C, 0);
  setSZP(cpu, cpu->A);
}

// ORI - Logical or Immediate With Accumulator
void ori(struct i8080 *cpu) {
  uint val = next_byte(cpu);

  cpu->A |= val;

  set_flag(cpu, FLAG_A, 0);
  set_flag(cpu, FLAG_C, 0);
  setSZP(cpu, cpu->A);
}

// ACI - Add Immediate to Accumulator With Carry
void aci(struct i8080 *cpu) {
  cpu->A = perform_add(cpu, cpu->A, next_byte(cpu), get_flag(cpu, FLAG_C));
}

// SBI - Subtract Immediate from Accumulator With Borrow
void sbi(struct i8080 *cpu) {
  cpu->A = perform_sub(cpu, cpu->A, next_byte(cpu), get_flag(cpu, FLAG_C));
}

// XRI - Logical Exclusive-Or Immediate With Accumulator
void xri(struct i8080 *cpu) {
  uint val = next_byte(cpu);
  cpu->A ^= val;

  set_flag(cpu, FLAG_C, 0);
  set_flag(cpu, FLAG_A, 0);
  setSZP(cpu, cpu->A);
}

// CPI - Compare Immediate With Accumulator
void cpi(struct i8080 *cpu) {
  perform_sub(cpu, cpu->A, next_byte(cpu), 0);
}

// CMP - Compare Memory or Register With Accumulator
void cmp(struct i8080 *cpu, uint opcode) {
  perform_sub(cpu, cpu->A, get_reg(cpu, opcode & 0x7), 0);
}

// ORA - Logical or Memory or Register with Accumulator
void ora(struct i8080 *cpu, uint opcode) {
  uint reg = opcode & 0x07;
  cpu->A |= get_reg(cpu, reg);

  set_flag(cpu, FLAG_A, 0);
  set_flag(cpu, FLAG_C, 0);
  setSZP(cpu, cpu->A);
}

// RLC - Rotate Accumulator Left
void rlc(struct i8080 *cpu) {
  uint hi_bit = (cpu->A & 0x80) ? 1 : 0;

  cpu->A <<= 1;
  cpu->A |= hi_bit;

  cpu->A &= 0xFF;

  set_flag(cpu, FLAG_C, hi_bit);
}

// RRC - Rotate Accumulator Right
void rrc(struct i8080 *cpu) {
  uint lo_bit = cpu->A & 0x01;

  cpu->A >>= 1;
  cpu->A |= (lo_bit << 7);
  cpu->A &= 0xFF;

  set_flag(cpu, FLAG_C, lo_bit);
}

// RAL - Rotate Accumulator Left Through Carry
void ral(struct i8080 *cpu) {
  uint old_carry = get_flag(cpu, FLAG_C) ? 1 : 0;

  set_flag(cpu, FLAG_C, cpu->A & 0x80);
  cpu->A <<= 1;
  cpu->A &= 0xFF;

  cpu->A |= old_carry & 0x01;
}

// RAR - Rotate Accumulator Right Through Carry
void rar(struct i8080 *cpu) {
  uint old_carry = get_flag(cpu, FLAG_C) ? 1 : 0;

  set_flag(cpu, FLAG_C, cpu->A & 0x01);
  cpu->A >>= 1;
  cpu->A &= 0xFF;

  cpu->A |= ((old_carry << 7) & 0x80);
}

// CMC - Complement Carry Bit
void cmc(struct i8080 *cpu) {
  set_flag(cpu, FLAG_C, !get_flag(cpu, FLAG_C));
}

// CMA - Complement Accumulator
void cma(struct i8080 *cpu) {
  cpu->A = (~cpu->A) & 0xFF;
}

// STC - Set Carry Bit
void stc(struct i8080 *cpu) {
  set_flag(cpu, FLAG_C, 1);
}

// DAD - Double Add
void dad(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;

  uint new_val = (CONCAT(cpu->H, cpu->L) + get_reg_pair(cpu, reg_pair));
  set_flag(cpu, FLAG_C, new_val & 0x10000);

  cpu->H = (new_val >> 8) & 0xFF;
  cpu->L = new_val & 0xFF;
}

// XCHG - Exchange Registers
void xchg(struct i8080 *cpu) {
  uint h_temp = cpu->H;
  uint l_temp = cpu->L;

  cpu->H = cpu->D;
  cpu->L = cpu->E;
  cpu->D = h_temp;
  cpu->E = l_temp;
}

// SPHL - Load SP from H and L
void sphl(struct i8080 *cpu) {
  cpu->SP = CONCAT(cpu->H, cpu->L);
}

// SHLD - Store H and L direct
void shld(struct i8080 *cpu) {
  uint addr = next_word(cpu);
  write_byte(cpu, addr, cpu->L);
  write_byte(cpu, addr + 1, cpu->H);
}

// LDHD - Load H and L direct
void ldhd(struct i8080 *cpu) {
  uint addr = next_word(cpu);
  cpu->L = read_byte(cpu, addr);
  cpu->H = read_byte(cpu, addr + 1);
}

// PUSH - Push Data Onto Stack
void push(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;

  // Register pair 3 refers to the concatenation of A and flags with push/pop
  uint data = reg_pair == 3 ? CONCAT(cpu->A, cpu->flags) : get_reg_pair(cpu, reg_pair);
  push_stackw(cpu, data);
}

// POP - Pop Data From Stack
void pop(struct i8080 *cpu, uint opcode) {
  uint reg_pair = (opcode & 0x30) >> 4;

  if (reg_pair == 3) { // PSW special case for push/pop
    cpu->flags = pop_stackb(cpu);

    cpu->flags |= 2; // Bit 1 of flags always set
    cpu->flags &= 0xD7; // Bits 3 and 5 of flags always reset

    cpu->A = pop_stackb(cpu);
  } else {
    set_reg_pair(cpu, reg_pair, pop_stackw(cpu));
  }
}

// XTHL - Exchange Stack
void xthl(struct i8080 *cpu) {
  uint temp_h = cpu->H;
  uint temp_l = cpu->L;

  cpu->L = read_byte(cpu, cpu->SP);
  cpu->H = read_byte(cpu, cpu->SP+1);

  write_byte(cpu, cpu->SP, temp_l);
  write_byte(cpu, cpu->SP+1, temp_h);
}

// CALL - Call
// CZ   - Call if Zero
// CNC  - Call if no Carry
// CC   - Call if Carry
// CPO  - Call if Parity Odd
// CPE  - Call if Parity Even
// CP   - Call if Plus
// CM   - Call if Minus
void general_call(struct i8080 *cpu, uint opcode) {
  // Unconditional call has LSB set, conditional calls do not
  if ((opcode & 1) || check_condition(cpu, (opcode >> 3) & 0x07)) {
    push_stackw(cpu, cpu->PC+2);
    cpu->PC = next_word(cpu);
  } else {
    cpu->PC += 2;
  }
}

// RET - Return
// RNZ - Return if not Zero
// RZ  - Return if Zero
// RNC - Return if no Carry
// RC  - Return if Carry
// RPO - Return if Parity Odd
// RPE - Return if Parity Even
// RP  - Return if Parity Odd
// RP  - Return if Plus
// RM  - Return if Minus
void general_return(struct i8080 *cpu, uint opcode) {
  // Unconditional return has LSB set, conditional returns do not
  if ((opcode & 1) || check_condition(cpu, (opcode >> 3) & 0x07)) {
    cpu->PC = pop_stackw(cpu);
  }
}

// JMP - Jump
// JNZ - Jump if not Zero
// JZ  - Jump if Zero
// JNC - Jump if no Carry
// JC  - Jump if Carry
// JPO - Jump if Parity Odd
// JPE - Jump if Parity Even
// JP  - Jump if Parity Odd
// JP  - Jump if Plus
// JM  - Jump if Minus
void general_jump(struct i8080 *cpu, uint opcode) {
  if ((opcode & 1) || check_condition(cpu, (opcode >> 3) & 0x07)) {
    cpu->PC = next_word(cpu);
  } else {
    cpu->PC += 2;
  }
}

// PCHL - Load Program Counter
void pchl(struct i8080 *cpu) {
  cpu->PC = CONCAT(cpu->H, cpu->L);
}

// EI - Enable Interrupts
void ei(struct i8080 *cpu) {
  cpu->INTE = 1;
}

// DI - Disable Interrupts
void di(struct i8080 *cpu) {
  cpu->INTE = 0;
}

// RST - Restart
void rst(struct i8080 *cpu, uint opcode) {
  push_stackw(cpu, cpu->PC);
  cpu->PC = opcode & 0x38;
}

// IN - Input
void in(struct i8080 *cpu) {
  uint dev = next_byte(cpu);
  if (cpu->input_handler != NULL) {
    cpu->A = cpu->input_handler(dev);
  }
}

void out(struct i8080 *cpu) {
  uint dev = next_byte(cpu);
  if (cpu->output_handler != NULL) {
    cpu->output_handler(dev, cpu->A);
  }
}

void step_cpu(struct i8080 *cpu) {
  if (cpu->halted) {
    return;
  }

  uint opcode = next_instruction_opcode(cpu);

  switch (opcode) {
    case 0x00: // NOP
    case 0x08: // NOP (alternate)
    case 0x10: // NOP (alternate)
    case 0x18: // NOP (alternate)
    case 0x20: // NOP (alternate)
    case 0x28: // NOP (alternate)
    case 0x30: // NOP (alternate)
    case 0x38: // NOP (alternate)
      nop(cpu);
      break;

    case 0x22: // SHLD a16
      shld(cpu);
      break;

    case 0x2A: // LDHD a16
      ldhd(cpu);
      break;

    case 0x2F: // CMA
      cma(cpu);
      break;

    case 0x3F: // CMC
      cmc(cpu);
      break;

    case 0x01: // LXI B, d16
    case 0x11: // LXI D, d16
    case 0x21: // LXI H, d16
    case 0x31: // LXI SP, d16
      lxi(cpu, opcode);
      break;

    case 0x09: // DAD B
    case 0x19: // DAD D
    case 0x29: // DAD H
    case 0x39: // DAD SP
      dad(cpu, opcode);
      break;

    case 0x37: // STC
      stc(cpu);
      break;

    case 0x02: // STAX B
    case 0x12: // STAX D
      stax(cpu, opcode);
      break;

    case 0x0A: // LDAX B
    case 0x1A: // LDAX D
      ldax(cpu, opcode);
      break;

    case 0x07: // RLC
      rlc(cpu);
      break;

    case 0x0F: // RRC
      rrc(cpu);
      break;

    case 0x17: // RAL
      ral(cpu);
      break;

    case 0x1F: // RAR
      rar(cpu);
      break;

    case 0x03: // INX B
    case 0x13: // INX D
    case 0x23: // INX H
    case 0x33: // INX SP
      inx(cpu, opcode);
      break;

    case 0x0B: // DCX B
    case 0x1B: // DCX D
    case 0x2B: // DCX H
    case 0x3B: // DCX SP
      dcx(cpu, opcode);
      break;

    case 0x04: // INR B
    case 0x0C: // INR C
    case 0x14: // INR D
    case 0x1C: // INR E
    case 0x24: // INR H
    case 0x2C: // INR L
    case 0x34: // INR M
    case 0x3C: // INR A
      inr(cpu, opcode);
      break;

    case 0x05: // DCR B
    case 0x0D: // DCR C
    case 0x15: // DCR D
    case 0x1D: // DCR E
    case 0x25: // DCR H
    case 0x2D: // DCR L
    case 0x35: // DCR M
    case 0x3D: // DCR A
      dcr(cpu, opcode);
      break;

    case 0x27: // DAA
      daa(cpu);
      break;

    case 0x06: // MVI B, d8
    case 0x0E: // MVI C, d8
    case 0x16: // MVI D, d8
    case 0x1E: // MVI E, d8
    case 0x2E: // MVI L, d8
    case 0x3E: // MVI A, d8
    case 0x26: // MVI H, d8
    case 0x36: // MVI M, d8
      mvi(cpu, opcode);
      break;

    case 0x32: // STA a16
      sta(cpu);
      break;

    case 0x3A: // LDA a16
      lda(cpu);
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
      mov(cpu, opcode);
      break;

    case 0x76: // HLT
      hlt(cpu);
      break;

    case 0x80: // ADD B
    case 0x81: // ADD C
    case 0x82: // ADD D
    case 0x83: // ADD E
    case 0x84: // ADD H
    case 0x85: // ADD L
    case 0x86: // ADD M
    case 0x87: // ADD A
      add(cpu, opcode);
      break;

    case 0x88: // ADC B
    case 0x89: // ADC C
    case 0x8A: // ADC D
    case 0x8B: // ADC E
    case 0x8C: // ADC H
    case 0x8D: // ADC L
    case 0x8E: // ADC M
    case 0x8F: // ADC A
      adc(cpu, opcode);
      break;

    case 0x90: // SUB B
    case 0x91: // SUB C
    case 0x92: // SUB D
    case 0x93: // SUB E
    case 0x94: // SUB H
    case 0x95: // SUB L
    case 0x96: // SUB M
    case 0x97: // SUB A
      sub(cpu, opcode);
      break;

    case 0x98: // SBB B
    case 0x99: // SBB C
    case 0x9A: // SBB D
    case 0x9B: // SBB E
    case 0x9C: // SBB H
    case 0x9D: // SBB L
    case 0x9E: // SBB M
    case 0x9F: // SBB A
      sbb(cpu, opcode);
      break;

    case 0xA0: // ANA B
    case 0xA1: // ANA C
    case 0xA2: // ANA D
    case 0xA3: // ANA E
    case 0xA4: // ANA H
    case 0xA5: // ANA L
    case 0xA6: // ANA M
    case 0xA7: // ANA A
      ana(cpu, opcode);
      break;

    case 0xDB: // IN d8
      in(cpu);
      break;

    case 0xD3: // OUT d8
      out(cpu);
      break;

    case 0xC6: // ADI d8
      adi(cpu);
      break;

    case 0xD6: // SUI d8
      sui(cpu);
      break;

    case 0xE6: // ANI d8
      ani(cpu);
      break;

    case 0xF6: // ORI d8
      ori(cpu);
      break;

    case 0xCE: // ACI d8
      aci(cpu);
      break;

    case 0xDE: // SBI d8
      sbi(cpu);
      break;

    case 0xEE: // XRI d8
      xri(cpu);
      break;

    case 0xFE: // CPI d8
      cpi(cpu);
      break;

    case 0xA8: // XRA B
    case 0xA9: // XRA C
    case 0xAA: // XRA D
    case 0xAB: // XRA E
    case 0xAC: // XRA H
    case 0xAD: // XRA L
    case 0xAE: // XRA M
    case 0xAF: // XRA A
      xra(cpu, opcode);
      break;

    case 0xB0: // ORA B
    case 0xB1: // ORA C
    case 0xB2: // ORA D
    case 0xB3: // ORA E
    case 0xB4: // ORA H
    case 0xB5: // ORA L
    case 0xB6: // ORA M
    case 0xB7: // ORA A
      ora(cpu, opcode);
      break;

    case 0xB8: // CMP B
    case 0xB9: // CMP C
    case 0xBA: // CMP D
    case 0xBB: // CMP E
    case 0xBC: // CMP H
    case 0xBD: // CMP L
    case 0xBE: // CMP M
    case 0xBF: // CMP A
      cmp(cpu, opcode);
      break;

    case 0xC1: // POP B
    case 0xD1: // POP D
    case 0xE1: // POP H
    case 0xF1: // POP PSW
      pop(cpu, opcode);
      break;

    case 0xC5: // PUSH B
    case 0xD5: // PUSH D
    case 0xE5: // PUSH H
    case 0xF5: // PUSH PSW
      push(cpu, opcode);
      break;

    case 0xC3: // JMP a16
    case 0xCB: // JMP a16 (alternate)
    case 0xC2: // JNZ a16
    case 0xCA: // JZ a16
    case 0xD2: // JNC a16
    case 0xDA: // JC a16
    case 0xE2: // JPO a16
    case 0xEA: // JPE a16
    case 0xF2: // JP a16
    case 0xFA: // JM a16
      general_jump(cpu, opcode);
      break;

    case 0xE9: // PCHL
      pchl(cpu);
      break;

    case 0xC9: // RET
    case 0xD9: // RET (alternate)
    case 0xC0: // RNZ
    case 0xC8: // RZ
    case 0xD0: // RNC
    case 0xD8: // RC
    case 0xE0: // RPO
    case 0xE8: // RPE
    case 0xF0: // RP
    case 0xF8: // RM
      general_return(cpu, opcode);
      break;

    case 0xC7: // RST 0
    case 0xCF: // RST 1
    case 0xD7: // RST 2
    case 0xDF: // RST 3
    case 0xE7: // RST 4
    case 0xEF: // RST 5
    case 0xF7: // RST 6
    case 0xFF: // RST 7
      rst(cpu, opcode);
      break;

    case 0xF3: // DI
      di(cpu);
      break;

    case 0xFB: // EI
      ei(cpu);
      break;

    case 0xCD: // CALL a16
    case 0xDD: // CALL a16 (alternate)
    case 0xED: // CALL a16 (alternate)
    case 0xFD: // CALL a16 (alternate)
    case 0xC4: // CNZ a16
    case 0xCC: // CZ a16
    case 0xD4: // CNC a16
    case 0xDC: // CC a16
    case 0xE4: // CPO a16
    case 0xEC: // CPE a16
    case 0xF4: // CP a16
    case 0xFC: // CM a16
      general_call(cpu, opcode);
      break;

    case 0xE3: // XTHL
      xthl(cpu);
      break;

    case 0xEB: // XCHG
      xchg(cpu);
      break;

    case 0xF9: // SPHL
      sphl(cpu);
      break;

    default:
      fprintf(stderr, "Opcode not implemented 0x%x\n", opcode);
      exit(1);
  }
}