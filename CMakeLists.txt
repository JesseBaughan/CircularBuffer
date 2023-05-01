cmake_minimum_required (VERSION 2.8)
project (Task2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

add_executable (exampleUsage exampleUsage.cpp CircularBuffer.cpp)

install (TARGETS exampleUsage DESTINATION bin)