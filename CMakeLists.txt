cmake_minimum_required(VERSION 3.2)

# ---[ enjoyDriving project
project(enjoyDriving)

# ---[ enjoyDriving version

#config parameters
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(ADDRESS_CFG_PATH "${PROJECT_SOURCE_DIR}/config/address.json")
set(DATA_CFG_PATH "${PROJECT_SOURCE_DIR}/data/")

configure_file (
  "${PROJECT_SOURCE_DIR}/config/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config/config.h"
  )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(PROJECT_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)

set(PROTOINCLUDEDIR ${CMAKE_CURRENT_BINARY_DIR}/src)
message("INCLUDE_DIR is ${PROJECT_INCLUDE_DIR}")

#install (FILES "${PROJECT_BINARY_DIR}/config.h"
#         DESTINATION include)
add_subdirectory(src)
add_subdirectory(examples)
