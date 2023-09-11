# Copyright (c) 2023 texer.ai. All rights reserved.
cmake_minimum_required(VERSION 3.0)

# Setting project directories.
set (SRC ../../source)

# Redirect to single build output location
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

set(ALL_H
    ${SRC}/parser/parser.h
    ${SRC}/common/token.h
    ${SRC}/common/ast.h
)

set(ALL_CPP
    ${SRC}/parser/parser.cpp
    ${SRC}/common/token.cpp
)

add_executable (parser_test ./main.cpp ${ALL_H} ${ALL_CPP})
target_include_directories(parser_test PRIVATE
    ${SRC}/common
    ${SRC}/parser
)
