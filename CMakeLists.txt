cmake_minimum_required(VERSION 3.0)

project(splat)

set(SRC ./source)

set(ALL_H
    ${SRC}/lexer.h
)

set(ALL_CPP
    ${SRC}/lexer.cpp
)
add_executable (splat ${SRC}/main.cpp ${ALL_H} ${ALL_CPP})