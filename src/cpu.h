#ifndef CPU_H
#define CPU_H

// Register pair convenience macros
#define CONCAT(HI, LO) (((HI << 8) | (LO & 0XFF)) & 0XFFFF)

#define RST_0 0xC7
#define RST_1 0xCF
#define RST_2 0xD7
#define RST_3 0xDF
#define RST_4 0xE7
#define RST_5 0xEF
#define RST_6 0xF7
#define RST_7 0xFF

struct cpu {
  int A, B, C, D, E;
  int H, L;
  int flags;
  int SP;
  int PC;
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

void request_interrupt(int);

void push_stackb(int);
void push_stackw(int);

int pop_stackb();
int pop_stackw();

#endif
