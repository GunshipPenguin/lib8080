#ifndef CPU_H
#define CPU_H

// Register pair convenience macros
#define CONCAT(HI, LO) (((HI << 8) | (LO & 0XFF)) & 0XFFFF)

#define FLAG_S (cpu->flags & 0x80)
#define FLAG_Z (cpu->flags & 0x40)
#define FLAG_A (cpu->flags & 0x10)
#define FLAG_P (cpu->flags & 0x02)
#define FLAG_C (cpu->flags & 0x01)

struct cpu {
  int A, B, C, D, E;
  int H, L;
  int flags;
  int SP;
  int PC;
};

struct cpu *cpu;

void create_cpu();
void step_cpu();

void reset_cpu();

#endif
