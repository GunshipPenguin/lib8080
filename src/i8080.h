#ifndef LIB8080_I8080_H_
#define LIB8080_I8080_H_

#include <stddef.h>

typedef unsigned int uint;
typedef uint (*i8080_in_handler)(uint);
typedef void (*i8080_out_handler)(uint, uint);

#define I8080_RST_0 0xC7
#define I8080_RST_1 0xCF
#define I8080_RST_2 0xD7
#define I8080_RST_3 0xDF
#define I8080_RST_4 0xE7
#define I8080_RST_5 0xEF
#define I8080_RST_6 0xF7
#define I8080_RST_7 0xFF

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

  i8080_in_handler input_handler;
  i8080_out_handler output_handler;
};

enum Flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

void reset_cpu(struct i8080 *);
void load_memory(struct i8080 *, char *, size_t);

void step_cpu(struct i8080 *);

void set_flag(struct i8080 *, enum Flag, int);
int get_flag(struct i8080 *, enum Flag);

void request_interrupt(struct i8080 *, uint);

void push_stackb(struct i8080 *, uint);
void push_stackw(struct i8080 *, uint);

uint pop_stackb(struct i8080 *);
uint pop_stackw(struct i8080 *);

uint read_byte(struct i8080 *, uint);
void write_byte(struct i8080 *, uint, uint);

uint read_word(struct i8080 *, uint);
void write_word(struct i8080 *, uint, uint);

#endif
