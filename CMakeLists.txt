cmake_minimum_required(VERSION 3.10)
project(altair C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(test)

SET(SRC_FILES src/cpu.c
              src/cpu.h
              src/memory.c
              src/memory.h)

SET(TEST_FILES
        test/attounit.h
        test/test.c
        test/cpu/mov_test.c
        test/cpu/mvi_test.c
        test/cpu/dcr_test.c
        test/cpu/inr_test.c
        test/cpu/nop_test.c
        test/cpu/add_test.c
        test/cpu/sub_test.c
        test/cpu/ora_test.c
        test/cpu/ana_test.c
        test/cpu/rlc_test.c
        test/cpu/rrc_test.c
        test/cpu/ral_test.c
        test/cpu/rar_test.c
        test/cpu/inx_test.c
        test/cpu/dcx_test.c
        test/cpu/jmp_test.c
        test/cpu/sta_test.c
        test/cpu/stax_test.c
        test/cpu/ldax_test.c
        test/cpu/lda_test.c
        test/cpu/lxi_test.c
        test/cpu/stc_test.c
        test/cpu/cmc_test.c
        test/cpu/cma_test.c
        test/cpu/dad_test.c
        test/cpu/xchg_test.c
        test/cpu/sphl_test.c
        test/cpu/shld_test.c
        test/cpu/ldhd_test.c)

add_executable(altair src/main.c ${SRC_FILES})
add_executable(altairtest ${SRC_FILES} ${TEST_FILES})