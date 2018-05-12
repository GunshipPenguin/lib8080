#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include "defs.h"

char* memory;
int memsize;

void create_memory(uint);
void load_memory(char *, size_t offset);

uint read_byte(uint);
void write_byte(uint, uint);

uint read_word(uint);
void write_word(uint, uint);

#endif
