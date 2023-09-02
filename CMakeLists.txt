cmake_minimum_required(VERSION 3.11.0)
project(optanestudy VERSION 0.1.0)

file(GLOB_RECURSE SOURCE_FILES src/kernel/memaccess.c src/kernel/debug.c)

set(CMAKE_C_FLAGS "-DAEP_SUPPORTED -mmmx -msse2 -mavx -mpreferred-stack-boundary=4 -g -O3")

add_executable(optanestudy ${SOURCE_FILES})

include_directories(optanestudy src/kernel/)