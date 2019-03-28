PROJECT(tools)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS thread program_options REQUIRED)
find_package(cppzmq)

# boost
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(testIbeoLux
               testIbeoLux.cpp
              )
target_link_libraries(testIbeoLux msgs
			${PROTOBUF_LIBRARIES} 
			${Boost_LIBRARIES} 
			${Boost_THREAD_LIBRARY}
                        msgs
                        cppzmq
                     )

add_executable(testTjuBusAcc testTjuBusAcc.cpp)
target_link_libraries(testTjuBusAcc
	      	${PROTOBUF_LIBRARIES} 
	      	${Boost_LIBRARIES} 
	      	${Boost_THREAD_LIBRARY}
                      cppzmq
                      common
                      msgs
                     )
