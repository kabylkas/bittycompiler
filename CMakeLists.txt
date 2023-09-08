# Copyright (c) 2023 texer.ai. All rights reserved.
cmake_minimum_required(VERSION 3.0)

project(bc)

# Setting compiler flags.
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${FLAGS})

# Tests.
add_subdirectory(./tests/lexer)
