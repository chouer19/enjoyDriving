project(orientus_examples)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wextra -Werror -Wno-missing-field-initializers -I . -O3")

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


ADD_EXECUTABLE(packet_example packet_example.cpp)
TARGET_LINK_LIBRARIES(packet_example ${rs232} ${orientus})


