PROJECT(actuation)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

find_library(can
             libcan.so
             ${PROJECT_LIB_DIR}
            )

if(NOT can)
message(FATAL_ERROR “can library not found”)
endif(NOT can)
message("found can library")

add_executable(TjuBusSteer TjuBusSteer.cpp)
target_link_libraries(TjuBusSteer
                        msgs
                        ${Boost_LIBRARIES}
                        ${Boost_THREAD_LIBRARY}
                        ${PROTOBUF_LIBRARIES}
                        ${can}
                        ${simdjson}
                        cppzmq
                        common
                      )

add_executable(TjuBusAcc TjuBusAcc.cpp)
target_link_libraries(TjuBusAcc
                        msgs
                        ${Boost_LIBRARIES}
                        ${Boost_THREAD_LIBRARY}
                        ${PROTOBUF_LIBRARIES}
                        ${can}
                        ${simdjson}
                        cppzmq
                        common
                      )
