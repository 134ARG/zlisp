cmake_minimum_required(VERSION 3.18)
project(zlisp C)

set(CMAKE_C_STANDARD 11)

add_executable(
  zlisp
  main.c
  src/lexer.c
  src/reader.c
  src/char_utils.c
  tests/unit_test.c
  src/tables.c
  src/logger.c
)

include_directories(include third_party)
