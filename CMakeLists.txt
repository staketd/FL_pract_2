cmake_minimum_required(VERSION 3.15)
project(pract_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        pract_2
        main.cpp
        Grammar/Grammar.cpp
        Grammar/Grammar.h
        Earley/Earley.cpp
        Earley/Earley.h
)

if(MINGW)
    set(GTEST_DISABLE_PTHREADS ON)
endif()

if(WIN32)
    set(WINDOWS_CMAKE_ARGS
            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
            )
else(WIN32)
    set(WINDOWS_CMAKE_ARGS )
endif(WIN32)

include_directories(
        Grammar
        Earley
)
include_directories(testing)

add_subdirectory(Grammar)
add_subdirectory(Earley)

enable_testing()
add_subdirectory(testing)