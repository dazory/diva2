# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/diva2/diva2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diva2/diva2/build

# Include any dependencies generated for this target.
include test/zmq/CMakeFiles/zmq_test.dir/depend.make

# Include the progress variables for this target.
include test/zmq/CMakeFiles/zmq_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/zmq/CMakeFiles/zmq_test.dir/flags.make

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o: test/zmq/CMakeFiles/zmq_test.dir/flags.make
test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o: ../test/zmq/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o"
	cd /home/diva2/diva2/build/test/zmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zmq_test.dir/main.cpp.o -c /home/diva2/diva2/test/zmq/main.cpp

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zmq_test.dir/main.cpp.i"
	cd /home/diva2/diva2/build/test/zmq && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/zmq/main.cpp > CMakeFiles/zmq_test.dir/main.cpp.i

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zmq_test.dir/main.cpp.s"
	cd /home/diva2/diva2/build/test/zmq && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/zmq/main.cpp -o CMakeFiles/zmq_test.dir/main.cpp.s

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.requires:

.PHONY : test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.requires

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.provides: test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.requires
	$(MAKE) -f test/zmq/CMakeFiles/zmq_test.dir/build.make test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.provides.build
.PHONY : test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.provides

test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.provides.build: test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o


# Object files for target zmq_test
zmq_test_OBJECTS = \
"CMakeFiles/zmq_test.dir/main.cpp.o"

# External object files for target zmq_test
zmq_test_EXTERNAL_OBJECTS =

test/zmq/zmq_test: test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o
test/zmq/zmq_test: test/zmq/CMakeFiles/zmq_test.dir/build.make
test/zmq/zmq_test: /usr/local/lib/libzmq.so
test/zmq/zmq_test: test/zmq/CMakeFiles/zmq_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable zmq_test"
	cd /home/diva2/diva2/build/test/zmq && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zmq_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/zmq/CMakeFiles/zmq_test.dir/build: test/zmq/zmq_test

.PHONY : test/zmq/CMakeFiles/zmq_test.dir/build

test/zmq/CMakeFiles/zmq_test.dir/requires: test/zmq/CMakeFiles/zmq_test.dir/main.cpp.o.requires

.PHONY : test/zmq/CMakeFiles/zmq_test.dir/requires

test/zmq/CMakeFiles/zmq_test.dir/clean:
	cd /home/diva2/diva2/build/test/zmq && $(CMAKE_COMMAND) -P CMakeFiles/zmq_test.dir/cmake_clean.cmake
.PHONY : test/zmq/CMakeFiles/zmq_test.dir/clean

test/zmq/CMakeFiles/zmq_test.dir/depend:
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/test/zmq /home/diva2/diva2/build /home/diva2/diva2/build/test/zmq /home/diva2/diva2/build/test/zmq/CMakeFiles/zmq_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/zmq/CMakeFiles/zmq_test.dir/depend

