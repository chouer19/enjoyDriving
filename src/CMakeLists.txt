PROJECT(src)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++17")

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

find_library(rs232
             librs232.so
             ${PROJECT_LIB_DIR}
            )

if(NOT rs232)
message(FATAL_ERROR “rs232 library not found”)
endif(NOT rs232)
message("found rs232 library")

find_library(orientus
             liborientus.so
             ${PROJECT_LIB_DIR}
            )

if(NOT orientus)
message(FATAL_ERROR “orientus library not found”)
endif(NOT orientus)
message("found orientus library")

include_directories(${PROTOINCLUDEDIR})
# boost
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

add_subdirectory(common)
add_subdirectory(msgs)
add_subdirectory(tools)
add_subdirectory(actuation)
add_subdirectory(liveDriver)

add_executable(test
               test.cpp
              )
target_link_libraries(test msgs
			${PROTOBUF_LIBRARIES} 
			${Boost_LIBRARIES} 
			${Boost_THREAD_LIBRARY}
                     )
