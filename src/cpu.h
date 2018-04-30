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
  int INTE;
};

enum Flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

struct cpu *cpu;

void create_cpu();
void step_cpu();

void reset_cpu();
void set_flag(enum Flag, int);
int get_flag(enum Flag);

void push_stackb(int);
void push_stackw(int);

int pop_stackb();
int pop_stackw();

#endif
