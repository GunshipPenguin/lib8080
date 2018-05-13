#ifndef CPU_H
#define CPU_H

#include "defs.h"

// Register pair convenience macros
#define CONCAT(HI, LO) (((HI << 8) | (LO & 0XFF)) & 0XFFFF)
#define TWOS_B(val) ((~(val) + 1) & 0xFF)

#define RST_0 0xC7
#define RST_1 0xCF
#define RST_2 0xD7
#define RST_3 0xDF
#define RST_4 0xE7
#define RST_5 0xEF
#define RST_6 0xF7
#define RST_7 0xFF

struct cpu {
  uint A, B, C, D, E;
  uint H, L;
  uint flags;
  uint SP;
  uint PC;
  int INTE;
  int halted;
};

enum Flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

struct cpu *cpu;

void create_cpu();
void step_cpu();

void reset_cpu();
void set_flag(enum Flag, int);
int get_flag(enum Flag);

void request_interrupt(uint);

void push_stackb(uint);
void push_stackw(uint);

uint pop_stackb();
uint pop_stackw();

#endif
