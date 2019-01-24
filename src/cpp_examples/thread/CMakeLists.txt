project(thread)

add_executable(
               testThread00
               testThread00.cpp
              )

target_link_libraries(
               testThread00
               pthread
)
