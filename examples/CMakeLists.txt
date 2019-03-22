PROJECT(exampls)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS thread program_options REQUIRED)
find_package(cppzmq)

find_library(ibeosdk
             libibeosdk.so
             ${PROJECT_LIB_DIR}
            )

if(NOT ibeosdk)
message(FATAL_ERROR “ibeosdk library not found”)
endif(NOT ibeosdk)
message("found ibeosdk library")

message(STATUS "#########################   DEMO   #############################")

include_directories(${PROTOINCLUDEDIR})
# boost
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

add_subdirectory(zmq_examples)
add_subdirectory(ibeo_examples)
add_subdirectory(proto_examples)
add_subdirectory(f710_examples)
add_subdirectory(cpp_examples)
add_subdirectory(orientus_examples)
add_subdirectory(simdjson_examples)
add_subdirectory(can_examples)

