#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void create_memory(struct i8080 *cpu, size_t size) {
  cpu->memsize = size;
  cpu->memory = malloc(size);
}

void free_memory(struct i8080 *cpu) {
  free(cpu->memory);
  cpu->memsize = 0;
}

void load_memory(struct i8080 *cpu, char *filename, size_t offset) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    exit(1);
  }

  for (int i=0;i<cpu->memsize;i++) {
    size_t res = fread(cpu->memory+(offset+i), sizeof(char), 1, file);

    if (res == 0) break;
  };

  fclose(file);
}

uint read_byte(struct i8080 *cpu, uint addr) {
  return cpu->memory[addr] & 0xFF;
}

uint read_word(struct i8080 *cpu, uint addr) {
  int hi = cpu->memory[addr+1] & 0xFF;
  int lo = cpu->memory[addr] & 0xFF;

  return (hi << 8) | lo;
}

void write_byte(struct i8080 *cpu, uint addr, uint data) {
  cpu->memory[addr] = (char) data;
}

void write_word(struct i8080 *cpu, uint addr, uint data) {
  char hi = (data >> 8) & 0xFF;
  char lo = data & 0xFF;

  cpu->memory[addr] = lo;
  cpu->memory[addr+1] = hi;
}