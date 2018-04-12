#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void create_memory(int size) {
  memsize = size;
  memory = malloc(size);
}

void load_memory(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    exit(1);
  }

  int addr = 0;
  while (addr < memsize) {
    size_t res = fread(memory+(addr++), sizeof(char), 1, file);

    if (res == 0) break;
  };

  fclose(file);
}

int read8(int addr) {
  return memory[addr] & 0xFF;
}

int read16(int addr) {
  int hi = memory[addr+1] & 0xFF;
  int lo = memory[addr] & 0xFF;

  return (hi << 8) | lo;
}

void write8(int addr, int data) {
  memory[addr] = (char) data;
}