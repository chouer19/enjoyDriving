project(f710_examples)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wextra -Werror -Wno-missing-field-initializers -I . -O3")

find_library(f710
             libf710.so
             ${PROJECT_LIB_DIR}
            )

if(NOT f710)
message(FATAL_ERROR “f710 library not found”)
endif(NOT f710)
message("found f710 library")


ADD_EXECUTABLE(testF710 testF710.cpp)
TARGET_LINK_LIBRARIES(testF710 ${f710})


