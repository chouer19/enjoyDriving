# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(pos320)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
               roscpp
               rospy
               std_msgs
               nav_msgs
               geometry_msgs
               genmsg
               zf_msgs
)

FIND_PACKAGE(Boost COMPONENTS system thread REQUIRED)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
# add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(driver src/driver.cpp)
add_executable(simulator src/simulator.cpp)
target_link_libraries(driver 
                             ${catkin_LIBRARIES}
                             ${Boost_SYSTEM_LIBRARY}
                             ${Boost_THREAD_LIBRARY}
                     )
target_link_libraries(simulator
                             ${catkin_LIBRARIES}
                             ${Boost_SYSTEM_LIBRARY}
                             ${Boost_THREAD_LIBRARY}
                     )
add_dependencies(simulator driver pos320_generate_messages_cpp)

# %EndTag(FULLTEXT)%
