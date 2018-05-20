cmake_minimum_required(VERSION 3.7.2)
project(altair C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(test/include)
include_directories()

SET(SRC_FILES src/cpu.c
              src/cpu.h
              src/memory.c
              src/memory.h
              src/defs.h)

SET(TEST_FILES
        test/include/attounit.h
        test/unit/test.c
        test/include/cpu_test_helpers.h
        test/unit/cpu/cpu_test_helpers.c
        test/unit/cpu/misc/interrupt_test.c
        test/unit/cpu/instructions/dcr_test.c
        test/unit/cpu/instructions/inr_test.c
        test/unit/cpu/instructions/nop_test.c
        test/unit/cpu/instructions/add_test.c
        test/unit/cpu/instructions/sub_test.c
        test/unit/cpu/instructions/ora_test.c
        test/unit/cpu/instructions/ana_test.c
        test/unit/cpu/instructions/jumps_test.c
        test/unit/cpu/instructions/xra_test.c
        test/unit/cpu/instructions/cmp_test.c
        test/unit/cpu/instructions/calls_test.c
        test/unit/cpu/instructions/returns_test.c
        test/unit/cpu/instructions/adc_test.c
        test/unit/cpu/instructions/register_pair_test.c
        test/unit/cpu/instructions/rotate_test.c
        test/unit/cpu/instructions/direct_test.c
        test/unit/cpu/instructions/data_transfer.c
        test/unit/cpu/instructions/carry_bit.c
        test/unit/cpu/instructions/cma_test.c
        test/unit/cpu/instructions/immediate_test.c
        test/unit/cpu/instructions/sbb_test.c
        test/unit/cpu/instructions/interrupt_instruction_test.c
        test/unit/cpu/instructions/daa_test.c
        test/unit/cpu/misc/stack_ops_test.c
        test/unit/cpu/misc/flags_test.c
        test/unit/cpu/misc/reset_cpu_test.c)

add_executable(i8080 src/main.c ${SRC_FILES})
add_executable(i8080test ${SRC_FILES} ${TEST_FILES})
add_executable(binloader test/integration/binloader.c ${SRC_FILES})