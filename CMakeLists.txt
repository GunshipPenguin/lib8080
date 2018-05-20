cmake_minimum_required(VERSION 3.7.2)
project(libi8080 C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(test/include)

SET(SRC_FILES src/i8080.c
              src/i8080.h)

SET(TEST_FILES
        test/include/attounit.h
        test/unit/test.c
        test/include/cpu_test_helpers.h
        test/unit/cpu_test_helpers.c
        test/unit/misc/interrupt_test.c
        test/unit/instructions/dcr_test.c
        test/unit/instructions/inr_test.c
        test/unit/instructions/nop_test.c
        test/unit/instructions/add_test.c
        test/unit/instructions/sub_test.c
        test/unit/instructions/ora_test.c
        test/unit/instructions/ana_test.c
        test/unit/instructions/jumps_test.c
        test/unit/instructions/xra_test.c
        test/unit/instructions/cmp_test.c
        test/unit/instructions/calls_test.c
        test/unit/instructions/returns_test.c
        test/unit/instructions/adc_test.c
        test/unit/instructions/register_pair_test.c
        test/unit/instructions/rotate_test.c
        test/unit/instructions/direct_test.c
        test/unit/instructions/data_transfer.c
        test/unit/instructions/carry_bit.c
        test/unit/instructions/cma_test.c
        test/unit/instructions/immediate_test.c
        test/unit/instructions/sbb_test.c
        test/unit/instructions/interrupt_instruction_test.c
        test/unit/instructions/daa_test.c
        test/unit/misc/stack_ops_test.c
        test/unit/misc/flags_test.c
        test/unit/misc/reset_cpu_test.c)

add_executable(i8080test ${SRC_FILES} ${TEST_FILES})
add_executable(binloader test/integration/binloader.c ${SRC_FILES})