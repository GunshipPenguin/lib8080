#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

char* memory;
int memsize;

void create_memory(int);
void load_memory(char *);

int read8(int);
void write8(int, int);

int read16(int);

#endif
