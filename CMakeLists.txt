cmake_minimum_required(VERSION 3.18)
project(zlisp C)

set(CMAKE_C_STANDARD 11)

add_executable(
  zlisp
  main.c
  src/lexer.c
  src/reader.c
  tests/unit_test.c
  src/tables.c
)

include_directories(include third_party)
