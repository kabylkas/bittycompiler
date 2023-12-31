# Copyright (c) 2023 texer.ai. All rights reserved.
cmake_minimum_required(VERSION 3.0)

# Setting project directories.
set (SRC ../../source)

# Redirect to single build output location
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

set(ALL_H
    ${SRC}/lexer/lexer.h
    ${SRC}/common/token.h
)

set(ALL_CPP
    ${SRC}/lexer/lexer.cpp
    ${SRC}/common/token.cpp
)

add_executable (lexer_test ./main.cpp ${ALL_H} ${ALL_CPP})
target_include_directories(lexer_test PRIVATE
    ${SRC}/common
    ${SRC}/lexer
)
