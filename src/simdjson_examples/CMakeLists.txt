project(simdjson_examples)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#set(CMAKE_CXX_FLAGS 
    #"${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wextra -Werror -Wno-missing-field-initializers -I . -O3")


find_library(simdjson
             libsimdjson.so
             ${PROJECT_LIB_DIR}
            )

if(NOT simdjson)
message(FATAL_ERROR “simdjson library not found”)
endif(NOT simdjson)
message("found simdjson library")

ADD_EXECUTABLE(readAddress readAddress.cpp)
TARGET_LINK_LIBRARIES(readAddress ${simdjson})

