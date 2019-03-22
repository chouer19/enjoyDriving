PROJECT(actuation)
set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11")

#add_executable(Pos320Driver
#               Pos320Driver.cpp
#              )
#target_link_libraries(Pos320Driver msgs
#			${PROTOBUF_LIBRARIES} 
#			${Boost_LIBRARIES} 
#			${Boost_THREAD_LIBRARY}
#                     )
#
#add_executable(IbeoLuxLiveDriver
#               IbeoLuxLiveDriver.cpp
#              )
#target_link_libraries(IbeoLuxLiveDriver 
#                      ${ibeosdk} 
#                      ${Boost_LIBRARIES} 
#                      ${Boost_PROGRAM_OPTIONS_LIBRARY}
#                      ${PROTOBUF_LIBRARIES}
#                      msgs
#                      cppzmq
#                     )
#
#ADD_EXECUTABLE(OrientusDriver OrientusDriver.cpp)
#TARGET_LINK_LIBRARIES(OrientusDriver ${rs232} ${orientus})
#
