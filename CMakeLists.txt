cmake_minimum_required (VERSION 2.8)
project (exampleUsage)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

add_executable (exampleUsage exampleUsage.cpp CircularBuffer/CircularBuffer.cpp)
target_include_directories(exampleUsage PUBLIC CircularBuffer)

install (TARGETS exampleUsage DESTINATION bin)