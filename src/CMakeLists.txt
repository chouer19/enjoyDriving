PROJECT(src)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)
set(PROTOINCLUDEDIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
add_subdirectory(proto)
add_subdirectory(zmq_examples)
add_subdirectory(ibeo_examples)

include_directories(${PROTOINCLUDEDIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${INCLUDE_DIR})

add_executable(writingMessageTest
               writingMessageTest.cc
              )
target_link_libraries(writingMessageTest 
                      proto
                      ${PROTOBUF_LIBRARIES}
                     )

add_executable(readingMessageTest
               readingMessageTest.cc
              )
target_link_libraries(readingMessageTest
                      proto
                      ${PROTOBUF_LIBRARIES}
                     )

add_executable(pos320Driver
               pos320Driver.cpp
              )
target_link_libraries(pos320Driver proto 
			${PROTOBUF_LIBRARIES} 
			${Boost_LIBRARIES} 
			${Boost_THREAD_LIBRARY}
			)
