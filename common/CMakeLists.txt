project(common)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-g -W -Wall -std=c++17")

find_library(simdjson
             libsimdjson.so
             ${PROJECT_LIB_DIR}
            )
add_library(common address.cpp)
target_link_libraries(common
                      ${simdjson})
