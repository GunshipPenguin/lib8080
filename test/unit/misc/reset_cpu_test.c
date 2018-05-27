#include <stdlib.h>
#include "i8080.h"
#include "attounit.h"
#include "cpu_test_helpers.h"

TEST_SUITE(i8080_reset)

struct i8080 *cpu;

BEFORE_EACH() {}
AFTER_EACH() {}

TEST_CASE(i8080_reset) {
  cpu = malloc(sizeof(struct i8080));
  i8080_reset(cpu);

  // Verify that everything is zeroed
  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->B, 0);
  ASSERT_EQUAL(cpu->C, 0);
  ASSERT_EQUAL(cpu->D, 0);
  ASSERT_EQUAL(cpu->E, 0);
  ASSERT_EQUAL(cpu->H, 0);
  ASSERT_EQUAL(cpu->L, 0);
  ASSERT_EQUAL(cpu->PC, 0);
  ASSERT_EQUAL(cpu->INTE, 0);
  ASSERT_EQUAL(cpu->flags, 2);
  ASSERT_EQUAL(cpu->SP, 0);
  ASSERT_EQUAL(cpu->halted, 0);
  ASSERT_EQUAL(cpu->pending_interrupt, 0);

  free(cpu);
}