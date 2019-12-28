cmake_minimum_required(VERSION 3.12)

project(Earley)

set(SOURCE_LIB Earley.cpp)

add_library(Earley STATIC ${SOURCE_LIB})