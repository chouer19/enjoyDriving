project(boost_thread)

find_package(Boost REQUIRED COMPONENTS thread chrono)

add_executable(01_thread 01_thread.cpp)
target_link_libraries(01_thread Boost::thread Boost::chrono)

add_executable(01_thread_withArgs 01_thread_withArgs.cpp)
target_link_libraries(01_thread_withArgs Boost::thread Boost::chrono)

add_executable(02_scoped_thread 02_scoped_thread.cpp)
target_link_libraries(02_scoped_thread Boost::thread Boost::chrono)

add_executable(03_interruption 03_interruption.cpp)
target_link_libraries(03_interruption Boost::thread Boost::chrono)

add_executable(04_disable_interruption 04_disable_interruption.cpp)
target_link_libraries(04_disable_interruption Boost::thread Boost::chrono)

add_executable(05_attributes 05_attributes.cpp)
target_link_libraries(05_attributes Boost::thread Boost::chrono)

add_executable(06_getidandprecessors 06_getidandprecessors.cpp)
target_link_libraries(06_getidandprecessors Boost::thread Boost::chrono)

add_executable(07_mutex 07_mutex.cpp)
target_link_libraries(07_mutex Boost::thread Boost::chrono)

add_executable(07_mutex_withArgs 07_mutex_withArgs.cpp)
target_link_libraries(07_mutex_withArgs Boost::thread Boost::chrono)

add_executable(08_lock_guard 08_lock_guard.cpp)
target_link_libraries(08_lock_guard Boost::thread Boost::chrono)

