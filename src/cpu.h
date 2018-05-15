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

struct i8080 {
  uint A, B, C, D, E;
  uint H, L;
  uint flags;
  uint SP;
  uint PC;
  int INTE;
  int halted;
  char *memory;
  size_t memsize;

  int pending_interrupt;
  uint interrupt_opcode;
};

enum Flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

struct i8080 *create_cpu();
void free_cpu(struct i8080 *);
void reset_cpu(struct i8080 *);

void step_cpu(struct i8080 *);

void set_flag(struct i8080 *, enum Flag, int);
int get_flag(struct i8080 *, enum Flag);

void request_interrupt(struct i8080 *, uint);

void push_stackb(struct i8080 *, uint);
void push_stackw(struct i8080 *, uint);

uint pop_stackb(struct i8080 *);
uint pop_stackw(struct i8080 *);

#endif
