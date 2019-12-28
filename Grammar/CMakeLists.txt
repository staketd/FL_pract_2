cmake_minimum_required(VERSION 3.12)

project(Grammar)

set(SOURCE_LIB Grammar.cpp)

add_library(Grammar STATIC ${SOURCE_LIB})