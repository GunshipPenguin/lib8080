#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

char* memory;
int memsize;

void create_memory(int);
void load_memory(char *);

int read_byte(int);
void write_byte(int, int);

int read_word(int);
void write_word(int, int);

#endif
