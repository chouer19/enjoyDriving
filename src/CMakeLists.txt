PROJECT(src)
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

set(PROTOINCLUDEDIR ${CMAKE_CURRENT_BINARY_DIR}/msgs)

include_directories(${PROTOINCLUDEDIR})
# boost
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

add_subdirectory(msgs)
add_subdirectory(zmq_examples)
add_subdirectory(ibeo_examples)
add_subdirectory(proto_examples)
add_subdirectory(f710_examples)
add_subdirectory(cpp_examples)
add_subdirectory(orientus_examples)
add_subdirectory(tools)

add_executable(Pos320Driver
               Pos320Driver.cpp
              )
target_link_libraries(Pos320Driver msgs
			${PROTOBUF_LIBRARIES} 
			${Boost_LIBRARIES} 
			${Boost_THREAD_LIBRARY}
                     )

add_executable(IbeoLuxLiveDriver
               IbeoLuxLiveDriver.cpp
              )
target_link_libraries(IbeoLuxLiveDriver 
                      ${ibeosdk} 
                      ${Boost_LIBRARIES} 
                      ${Boost_PROGRAM_OPTIONS_LIBRARY}
                      ${PROTOBUF_LIBRARIES}
                      msgs
                      cppzmq
                     )

add_executable(test
               test.cpp
              )
target_link_libraries(test msgs
			${PROTOBUF_LIBRARIES} 
			${Boost_LIBRARIES} 
			${Boost_THREAD_LIBRARY}
                     )

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


ADD_EXECUTABLE(OrientusDriver OrientusDriver.cpp)
TARGET_LINK_LIBRARIES(OrientusDriver ${rs232} ${orientus})

