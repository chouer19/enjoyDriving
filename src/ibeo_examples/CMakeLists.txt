cmake_minimum_required(VERSION 3.12)
project(ibeosdk_demos)

find_library(ibeosdk
             libibeosdk.so
             /home/xuechong/workspace/ibeo/ibeosdk_backup/libs)

if(NOT ibeosdk)
message(FATAL_ERROR “ibeosdk library not found”)
endif(NOT ibeosdk)
message("found ibeosdk library")

message(STATUS "#########################   DEMO   #############################")

# parse demo files
#######################################################
# Collect all demo files
#######################################################
file(GLOB DEMO_SOURCES *.cpp)

#######################################################
include_directories(/home/xuechong/workspace/ibeo/IbeoSDK5.2.2/src)

#######################################################
# boost
#######################################################
FIND_PACKAGE(Boost COMPONENTS thread program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#######################################################
# create demos
#######################################################

foreach(demo ${DEMO_SOURCES})
    get_filename_component(demoName "${demo}" NAME_WE)
    add_executable(${demoName} ${demo})
    target_link_libraries(${demoName} ${ibeosdk} ${Boost_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})
endforeach()

