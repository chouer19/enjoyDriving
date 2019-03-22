project(thread)


# parse demo files
#######################################################
# Collect all demo files
#######################################################
file(GLOB DEMO_SOURCES *.cpp)

#######################################################
#######################################################
# boost
#######################################################
FIND_PACKAGE(Boost COMPONENTS thread program_options REQUIRED)

#######################################################
# create demos
#######################################################

foreach(demo ${DEMO_SOURCES})
    get_filename_component(demoName "${demo}" NAME_WE)
    add_executable(${demoName} ${demo})
    target_link_libraries(${demoName} pthread)
endforeach()

