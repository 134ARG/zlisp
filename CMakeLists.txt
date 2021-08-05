cmake_minimum_required(VERSION 3.18)
project(zlisp C)

set(CMAKE_C_STANDARD 11)

add_executable(zlisp main.c include/string_utils.h include/status.h include/mem_utils.h src/lexer.c include/context.h include/char_utils.h include/lexer.h tests/unit_test.c include/unit_test.h include/logger.h include/check.h src/list.c include/list.h include/tables.h src/tables.c)

include_directories(include third_party)