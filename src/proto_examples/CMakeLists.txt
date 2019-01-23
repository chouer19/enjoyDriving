PROJECT(proto_examples)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS thread program_options REQUIRED)

find_library(ibeosdk
             libibeosdk.so
             ${PROJECT_LIB_DIR}
            )


include_directories(${PROTOINCLUDEDIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(writingMessageTest
               writingMessageTest.cpp
              )
target_link_libraries(writingMessageTest 
                      msgs
                      ${PROTOBUF_LIBRARIES}
                     )

add_executable(readingMessageTest
               readingMessageTest.cpp
              )
target_link_libraries(readingMessageTest
                      msgs
                      ${PROTOBUF_LIBRARIES}
                     )

add_executable(importMessageTest
               importMessageTest.cpp
              )
target_link_libraries(importMessageTest
                      msgs
                      ${ibeosdk}
                      ${PROTOBUF_LIBRARIES}
                      ${Boost_LIBRARIES}
                     )

