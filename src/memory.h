#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include "defs.h"
#include "cpu.h"

void create_memory(struct i8080 *, size_t);
void load_memory(struct i8080 *, char *, size_t);
void free_memory(struct i8080 *);

uint read_byte(struct i8080 *, uint);
void write_byte(struct i8080 *, uint, uint);

uint read_word(struct i8080 *, uint);
void write_word(struct i8080 *, uint, uint);

#endif
