cmake_minimum_required(VERSION 3.27)

project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Day1P1 Day1P1.cpp "Day1P1.cpp")
add_executable(Day1P2 Day1P2.cpp "Day1P2.cpp")

file(COPY Inputs DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")