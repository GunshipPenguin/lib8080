#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void create_memory(int size) {
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

int read_byte(int addr) {
  return memory[addr] & 0xFF;
}

int read_word(int addr) {
  int hi = memory[addr+1] & 0xFF;
  int lo = memory[addr] & 0xFF;

  return (hi << 8) | lo;
}

void write_byte(int addr, int data) {
  memory[addr] = (char) data;
}

void write_word(int addr, int data) {
  char hi = (data >> 8) & 0xFF;
  char lo = data & 0xFF;

  memory[addr] = lo;
  memory[addr+1] = hi;
}