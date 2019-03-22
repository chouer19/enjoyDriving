cmake_minimum_required(VERSION 3.3)

project(can_examples LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-D_GNU_SOURCE)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-parentheses")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSO_RXQ_OVFL=40")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPF_CAN=29")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAF_CAN=PF_CAN")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DN_SLCAN=17")

find_library(can
             libcan.so
             ${PROJECT_LIB_DIR}
            )

#if(NOT ibeosdk)
#message(FATAL_ERROR “ibeosdk library not found”)
#endif(NOT ibeosdk)
#message("found ibeosdk library")


add_executable(cansend cansend.c)
add_executable(candump candump.c)
add_executable(cantest cantest.c)
add_executable(canrcv canrcv.c)

target_link_libraries(cansend ${can})
target_link_libraries(candump ${can})
target_link_libraries(cantest ${can})
target_link_libraries(canrcv ${can})
