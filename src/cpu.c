#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"

struct cpu *cpu = NULL;

const int ins_sizes[] = {
//0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
  1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0
  1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 1
  1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1, // 2
  1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1, // 3
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 4
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 5
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 6
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 7
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 8
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 9
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // A
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // B
  1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3, 3, 3, 3, 2, 1, // C
  1, 1, 3, 2, 3, 1, 2, 1, 1, 1, 3, 2, 3, 3, 2, 1, // D
  1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1, // E
  1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1  // F
};

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
  cpu->flags = 0;
  cpu->SP = 0;
}

void set_reg(int reg, int val) {
  switch(reg) {
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
    case 6: write8(CONCAT(cpu->H, cpu->L), val);
  }
}

int get_reg(int reg) {
  switch(reg) {
    case 7: return cpu->A;
    case 0: return cpu->B;
    case 1: return cpu->C;
    case 2: return cpu->D;
    case 3: return cpu->E;
    case 4: return cpu->H;
    case 5: return cpu->L;
    case 6: return read8(CONCAT(cpu->H, cpu->L));
  }

  fprintf(stderr, "Invalid register %d\n", reg);
  exit(1);
}

int get_reg_pair(int reg_pair) {
  switch (reg_pair) {
    case 0: return CONCAT(cpu->B, cpu->C);
    case 1: return CONCAT(cpu->D, cpu->E);
    case 2: return CONCAT(cpu->H, cpu->L);
    case 3: return cpu->SP;
  }

  fprintf(stderr, "Invalid register pair %d\n", reg_pair);
  exit(1);
}


void set_reg_pair(int reg_pair, int val) {
  int hi = val & 0xFF;
  int lo = (val >> 8) & 0xFF;

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
      cpu->SP = val;
      break;
  }

  fprintf(stderr, "Invalid register pair %d\n", reg_pair);
}

// Instructions follow
void hlt() {

}

void nop() {

}

void jmp() {
  cpu->PC = read16(cpu->PC+1);
}

void mov(int opcode) {
  int dst = (opcode & 0x38) >> 3;
  int src = opcode & 0x07;

  set_reg(dst, get_reg(src));
}

void mvi(int opcode) {
  int reg = (opcode & 0x38) >> 3;
  set_reg(reg, read8(cpu->PC+1));
}

void sta() {
  write8(read16(cpu->PC+1), cpu->A);
}

void inr(int opcode) {
  int reg = (opcode & 0x38) >> 3;
  set_reg(reg, get_reg(reg)+1);
}

void dcr(int opcode) {
  int reg = (opcode & 0x38) >> 3;
  set_reg(reg, get_reg(reg)-1);
}

void inx(int opcode) {
  int reg = (opcode & 0x30) >> 4;
  set_reg_pair(reg, get_reg_pair(reg)+1);
}

void dcx(int opcode) {
  int reg = (opcode & 0x30) >> 4;
  set_reg_pair(reg, get_reg_pair(reg)-1);
}

void step_cpu() {
  int opcode = read8(cpu->PC);

  switch (opcode) {
    case 0x00: // NOP
    case 0x10: // NOP
    case 0x20: // NOP
    case 0x30: // NOP
      nop();
      break;

    case 0x03: // INX B
    case 0x13: // INX D
    case 0x23: // INX H
    case 0x33: // INX SP
      inx(opcode);

    case 0x0B: // DCX B
    case 0x1B: // DCX D
    case 0x2B: // DCX H
    case 0x3B: // DCX SP
      dcx(opcode);

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

    case 0x32: // STA d8
      sta();

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

    case 0xC3: // JMP
      jmp();
      break;

    default:
      fprintf(stderr, "Opcode not implemented 0x%x", opcode);
      exit(1);
  }

//  printf("%x %x %x\n", cpu->A, cpu->B, cpu->PC);
  cpu->PC += ins_sizes[opcode];
}