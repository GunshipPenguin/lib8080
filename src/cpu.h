#ifndef CPU_H
#define CPU_H

// Register pair convenience macros
#define CONCAT(HI, LO) (((HI << 8) | (LO & 0XFF)) & 0XFFFF)

struct cpu {
  int A, B, C, D, E;
  int H, L;
  int flags;
  int SP;
  int PC;
};

enum Flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

struct cpu *cpu;

void create_cpu();
void step_cpu();

void reset_cpu();
void set_flag(enum Flag, int);
int get_flag(enum Flag);

void push_stack8(int);
void push_stack16(int);

int pop_stack8();
int pop_stack16();

#endif
