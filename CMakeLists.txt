cmake_minimum_required(VERSION 3.10)
project(altair C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(test)

SET(SRC_FILES src/cpu.c
              src/cpu.h
              src/memory.c
              src/memory.h)

SET(TEST_FILES test/attounit.h
               test/test.c
               test/mov_test.c
               test/mvi_test.c
               test/dcr_test.c
               test/inr_test.c)

add_executable(altair src/main.c ${SRC_FILES})
add_executable(altairtest ${SRC_FILES} ${TEST_FILES})