#ifndef LIB8080_H_
#define LIB8080_H_

#include <stddef.h>

typedef unsigned int uint;

struct i8080;
typedef uint (*i8080_in_handler)(struct i8080 *, uint);
typedef void (*i8080_out_handler)(struct i8080 *, uint, uint);

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

  uint cyc;
};

enum i8080_flag {FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C};

void i8080_reset(struct i8080 *);
void i8080_load_memory(struct i8080 *, char *, size_t);

void i8080_step(struct i8080 *);

void i8080_set_flag(struct i8080 *, enum i8080_flag, int);
int i8080_get_flag(struct i8080 *, enum i8080_flag);

void i8080_request_interrupt(struct i8080 *, uint);

void i8080_push_stackb(struct i8080 *, uint);
void i8080_push_stackw(struct i8080 *, uint);

uint i8080_pop_stackw(struct i8080 *);
uint i8080_pop_stackb(struct i8080 *);

uint i8080_read_byte(struct i8080 *, uint);
void i8080_write_byte(struct i8080 *, uint, uint);

uint i8080_read_word(struct i8080 *, uint);
void i8080_write_word(struct i8080 *, uint, uint);

#endif
