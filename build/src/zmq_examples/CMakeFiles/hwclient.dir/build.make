# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xuechong/workspace/enterprise/enjoyDriving

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuechong/workspace/enterprise/enjoyDriving/build

# Include any dependencies generated for this target.
include src/zmq_examples/CMakeFiles/hwclient.dir/depend.make

# Include the progress variables for this target.
include src/zmq_examples/CMakeFiles/hwclient.dir/progress.make

# Include the compile flags for this target's objects.
include src/zmq_examples/CMakeFiles/hwclient.dir/flags.make

src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.o: src/zmq_examples/CMakeFiles/hwclient.dir/flags.make
src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.o: ../src/zmq_examples/hwclient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuechong/workspace/enterprise/enjoyDriving/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.o"
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hwclient.dir/hwclient.cpp.o -c /home/xuechong/workspace/enterprise/enjoyDriving/src/zmq_examples/hwclient.cpp

src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hwclient.dir/hwclient.cpp.i"
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuechong/workspace/enterprise/enjoyDriving/src/zmq_examples/hwclient.cpp > CMakeFiles/hwclient.dir/hwclient.cpp.i

src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hwclient.dir/hwclient.cpp.s"
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuechong/workspace/enterprise/enjoyDriving/src/zmq_examples/hwclient.cpp -o CMakeFiles/hwclient.dir/hwclient.cpp.s

# Object files for target hwclient
hwclient_OBJECTS = \
"CMakeFiles/hwclient.dir/hwclient.cpp.o"

# External object files for target hwclient
hwclient_EXTERNAL_OBJECTS =

bin/hwclient: src/zmq_examples/CMakeFiles/hwclient.dir/hwclient.cpp.o
bin/hwclient: src/zmq_examples/CMakeFiles/hwclient.dir/build.make
bin/hwclient: src/msgs/libmsgs.a
bin/hwclient: /usr/local/lib/libprotobuf.so
bin/hwclient: /usr/local/lib/libzmq.so.5.2.1
bin/hwclient: src/zmq_examples/CMakeFiles/hwclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuechong/workspace/enterprise/enjoyDriving/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/hwclient"
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hwclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/zmq_examples/CMakeFiles/hwclient.dir/build: bin/hwclient

.PHONY : src/zmq_examples/CMakeFiles/hwclient.dir/build

src/zmq_examples/CMakeFiles/hwclient.dir/clean:
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples && $(CMAKE_COMMAND) -P CMakeFiles/hwclient.dir/cmake_clean.cmake
.PHONY : src/zmq_examples/CMakeFiles/hwclient.dir/clean

src/zmq_examples/CMakeFiles/hwclient.dir/depend:
	cd /home/xuechong/workspace/enterprise/enjoyDriving/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuechong/workspace/enterprise/enjoyDriving /home/xuechong/workspace/enterprise/enjoyDriving/src/zmq_examples /home/xuechong/workspace/enterprise/enjoyDriving/build /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples /home/xuechong/workspace/enterprise/enjoyDriving/build/src/zmq_examples/CMakeFiles/hwclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/zmq_examples/CMakeFiles/hwclient.dir/depend

