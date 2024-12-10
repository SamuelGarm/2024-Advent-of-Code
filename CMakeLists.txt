cmake_minimum_required(VERSION 3.27)

project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(dayNum RANGE 1 9)
add_executable(Day${dayNum} "Day${dayNum}.cpp")
endforeach()

file(COPY Inputs DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")