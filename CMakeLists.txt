cmake_minimum_required(VERSION 3.7.2)
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
        test/unit/test.c
        test/unit/cpu/dcr_test.c
        test/unit/cpu/inr_test.c
        test/unit/cpu/nop_test.c
        test/unit/cpu/add_test.c
        test/unit/cpu/sub_test.c
        test/unit/cpu/ora_test.c
        test/unit/cpu/ana_test.c
        test/unit/cpu/jumps_test.c
        test/unit/cpu/xra_test.c
        test/unit/cpu/cmp_test.c
        test/unit/cpu/calls_test.c
        test/unit/cpu/returns_test.c
        test/unit/cpu/adc_test.c
        test/unit/cpu/cpu_test_helpers.h
        test/unit/cpu/cpu_test_helpers.c
        test/unit/cpu/register_pair_test.c
        test/unit/cpu/rotate_test.c
        test/unit/cpu/direct_test.c
        test/unit/cpu/data_transfer.c
        test/unit/cpu/carry_bit.c
        test/unit/cpu/cma_test.c
        test/unit/cpu/immediate_test.c
        test/unit/cpu/sbb_test.c
        test/unit/cpu/interrupt_instruction_test.c
        test/unit/cpu/interrupt_test.c
        test/unit/cpu/daa_test.c)

add_executable(i8080 src/main.c ${SRC_FILES})
add_executable(i8080test ${SRC_FILES} ${TEST_FILES})
add_executable(binloader test/integration/binloader.c ${SRC_FILES})