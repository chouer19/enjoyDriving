cmake_minimum_required(VERSION 3.2)

# ---[ enjoyDriving project
project(enjoyDriving)

# ---[ enjoyDriving version

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIB_DIR ${PROJECT_BINARY_DIR}/lib)
set(INCLUDE_DIR ${PROJECT_BINARY_DIR}/include)

add_subdirectory(src)
