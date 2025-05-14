cmake_minimum_required(VERSION 3.12)
project("laba3" CXX)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_executable("laba3" "main.cpp" "HashTable.h" "Pair.h")