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
include test/socketCan/CMakeFiles/socketCan.dir/depend.make

# Include the progress variables for this target.
include test/socketCan/CMakeFiles/socketCan.dir/progress.make

# Include the compile flags for this target's objects.
include test/socketCan/CMakeFiles/socketCan.dir/flags.make

test/socketCan/sensors.pb.cc: ../test/protobuf/sensors.proto
test/socketCan/sensors.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on ../protobuf/sensors.proto"
	cd /home/diva2/diva2/build/test/socketCan && /usr/local/bin/protoc --cpp_out=/home/diva2/diva2/build/test/socketCan -I /home/diva2/diva2/test/protobuf /home/diva2/diva2/test/protobuf/sensors.proto

test/socketCan/sensors.pb.h: test/socketCan/sensors.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate test/socketCan/sensors.pb.h

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o: test/socketCan/CMakeFiles/socketCan.dir/flags.make
test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o: ../test/socketCan/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socketCan.dir/test.cpp.o -c /home/diva2/diva2/test/socketCan/test.cpp

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socketCan.dir/test.cpp.i"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/socketCan/test.cpp > CMakeFiles/socketCan.dir/test.cpp.i

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socketCan.dir/test.cpp.s"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/socketCan/test.cpp -o CMakeFiles/socketCan.dir/test.cpp.s

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.requires:

.PHONY : test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.requires

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.provides: test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.requires
	$(MAKE) -f test/socketCan/CMakeFiles/socketCan.dir/build.make test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.provides.build
.PHONY : test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.provides

test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.provides.build: test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o


test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o: test/socketCan/CMakeFiles/socketCan.dir/flags.make
test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o: test/socketCan/sensors.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socketCan.dir/sensors.pb.cc.o -c /home/diva2/diva2/build/test/socketCan/sensors.pb.cc

test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socketCan.dir/sensors.pb.cc.i"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/build/test/socketCan/sensors.pb.cc > CMakeFiles/socketCan.dir/sensors.pb.cc.i

test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socketCan.dir/sensors.pb.cc.s"
	cd /home/diva2/diva2/build/test/socketCan && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/build/test/socketCan/sensors.pb.cc -o CMakeFiles/socketCan.dir/sensors.pb.cc.s

test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.requires:

.PHONY : test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.requires

test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.provides: test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.requires
	$(MAKE) -f test/socketCan/CMakeFiles/socketCan.dir/build.make test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.provides.build
.PHONY : test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.provides

test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.provides.build: test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o


# Object files for target socketCan
socketCan_OBJECTS = \
"CMakeFiles/socketCan.dir/test.cpp.o" \
"CMakeFiles/socketCan.dir/sensors.pb.cc.o"

# External object files for target socketCan
socketCan_EXTERNAL_OBJECTS =

test/socketCan/socketCan: test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o
test/socketCan/socketCan: test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o
test/socketCan/socketCan: test/socketCan/CMakeFiles/socketCan.dir/build.make
test/socketCan/socketCan: /usr/local/lib/libzmq.so
test/socketCan/socketCan: /usr/local/lib/libprotobuf.so
test/socketCan/socketCan: /usr/local/lib/libzmq.so
test/socketCan/socketCan: /usr/local/lib/libprotobuf.so
test/socketCan/socketCan: test/socketCan/CMakeFiles/socketCan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable socketCan"
	cd /home/diva2/diva2/build/test/socketCan && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socketCan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/socketCan/CMakeFiles/socketCan.dir/build: test/socketCan/socketCan

.PHONY : test/socketCan/CMakeFiles/socketCan.dir/build

test/socketCan/CMakeFiles/socketCan.dir/requires: test/socketCan/CMakeFiles/socketCan.dir/test.cpp.o.requires
test/socketCan/CMakeFiles/socketCan.dir/requires: test/socketCan/CMakeFiles/socketCan.dir/sensors.pb.cc.o.requires

.PHONY : test/socketCan/CMakeFiles/socketCan.dir/requires

test/socketCan/CMakeFiles/socketCan.dir/clean:
	cd /home/diva2/diva2/build/test/socketCan && $(CMAKE_COMMAND) -P CMakeFiles/socketCan.dir/cmake_clean.cmake
.PHONY : test/socketCan/CMakeFiles/socketCan.dir/clean

test/socketCan/CMakeFiles/socketCan.dir/depend: test/socketCan/sensors.pb.cc
test/socketCan/CMakeFiles/socketCan.dir/depend: test/socketCan/sensors.pb.h
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/test/socketCan /home/diva2/diva2/build /home/diva2/diva2/build/test/socketCan /home/diva2/diva2/build/test/socketCan/CMakeFiles/socketCan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/socketCan/CMakeFiles/socketCan.dir/depend

