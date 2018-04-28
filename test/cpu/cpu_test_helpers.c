#include "cpu.h"
#include "memory.h"

/**
 * @brief Setup a small test environment for CPU tests
 *
 * This function sets up a test environment suitable for testing CPU
 * functionality.
 *
 * Specifically, this function sets up a machine with
 * - 32 Bytes of memory, all initialized to 0x00
 * - Stack pointer initialized to 0x10
 * - FLAGS register initialized to 0x02
 * - All other registers (including the program counter) initialized to 0x00
 */
void setup_cpu_test_env() {
  if (cpu == NULL) {
    create_cpu();
  }

  // Set all registers/flags to 0
  reset_cpu();

  if (memory == NULL) {
    create_memory(32);
  }

  // Zero out memory
  for (int i=0;i<32;i++) {
    write_byte(i, 0);
  }

  cpu->SP = 16;
}