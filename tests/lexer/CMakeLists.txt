# Copyright (c) 2023 texer.ai. All rights reserved.
cmake_minimum_required(VERSION 3.0)

# Setting project directories.
set (SRC ../../source)

set(ALL_H
    ${SRC}/common/token.h
    ${SRC}/lexer/lexer.h
)

set(ALL_CPP
    ${SRC}/lexer/lexer.cpp
)

add_executable (lexer_test ./main.cpp ${ALL_H} ${ALL_CPP})
target_include_directories(lexer_test PRIVATE
    ${SRC}/common
    ${SRC}/lexer
)
