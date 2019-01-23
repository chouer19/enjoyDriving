cmake_minimum_required(VERSION 3.2)

# ---[ enjoyDriving project
project(enjoyDriving)

# ---[ enjoyDriving version

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(PROJECT_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
message("INCLUDE_DIR is ${PROJECT_INCLUDE_DIR}")

add_subdirectory(src)
