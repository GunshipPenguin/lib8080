#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void create_memory(uint size) {
  memsize = size;
  memory = malloc(size);
}

void load_memory(char *filename, size_t offset) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    exit(1);
  }

  size_t addr = offset;
  for (int i=0;i<memsize;i++) {
    size_t res = fread(memory+(offset+i), sizeof(char), 1, file);

    if (res == 0) break;
  };

  fclose(file);
}

uint read_byte(uint addr) {
  return memory[addr] & 0xFF;
}

uint read_word(uint addr) {
  int hi = memory[addr+1] & 0xFF;
  int lo = memory[addr] & 0xFF;

  return (hi << 8) | lo;
}

void write_byte(uint addr, uint data) {
  memory[addr] = (char) data;
}

void write_word(uint addr, uint data) {
  char hi = (data >> 8) & 0xFF;
  char lo = data & 0xFF;

  memory[addr] = lo;
  memory[addr+1] = hi;
}