cmake_minimum_required(VERSION 3.15)
project(pract_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        pract_2
        main.cpp
        Grammar/Grammar.cpp
        Grammar/Grammar.h
)

include_directories(
        Grammar
        Earley
)
add_subdirectory(Grammar)
add_subdirectory(Earley)
