#ifndef CPU_TEST_HELPERS_H
#define CPU_TEST_HELPERS_H

struct i8080 *setup_cpu_test_env();
void teardown_cpu_test_env(struct i8080 *);

#endif