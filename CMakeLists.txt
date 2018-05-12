cmake_minimum_required(VERSION 3.10)
project(altair C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(test)

SET(SRC_FILES src/cpu.c
              src/cpu.h
              src/memory.c
              src/memory.h)

SET(TEST_FILES
        test/attounit.h
        test/test.c
        test/cpu/dcr_test.c
        test/cpu/inr_test.c
        test/cpu/nop_test.c
        test/cpu/add_test.c
        test/cpu/sub_test.c
        test/cpu/ora_test.c
        test/cpu/ana_test.c
        test/cpu/jumps_test.c
        test/cpu/xra_test.c
        test/cpu/cmp_test.c
        test/cpu/calls_test.c
        test/cpu/returns_test.c
        test/cpu/adc_test.c
        test/cpu/cpu_test_helpers.h
        test/cpu/cpu_test_helpers.c
        test/cpu/register_pair_test.c
        test/cpu/rotate_test.c
        test/cpu/direct_test.c
        test/cpu/data_transfer.c
        test/cpu/carry_bit.c
        test/cpu/cma_test.c
        test/cpu/immediate_test.c
        test/cpu/sbb_test.c
        test/cpu/interrupt_instruction_test.c
        test/cpu/interrupt_test.c
        test/cpu/daa_test.c)

add_executable(i8080 src/main.c ${SRC_FILES})
add_executable(i8080test ${SRC_FILES} ${TEST_FILES})
