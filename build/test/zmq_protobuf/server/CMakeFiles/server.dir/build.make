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
include test/zmq_protobuf/server/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include test/zmq_protobuf/server/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include test/zmq_protobuf/server/CMakeFiles/server.dir/flags.make

test/zmq_protobuf/server/message.pb.cc: ../test/zmq_protobuf/server/message.proto
test/zmq_protobuf/server/message.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on message.proto"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/local/bin/protoc --cpp_out=/home/diva2/diva2/build/test/zmq_protobuf/server -I /home/diva2/diva2/test/zmq_protobuf/server /home/diva2/diva2/test/zmq_protobuf/server/message.proto

test/zmq_protobuf/server/message.pb.h: test/zmq_protobuf/server/message.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate test/zmq_protobuf/server/message.pb.h

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o: test/zmq_protobuf/server/CMakeFiles/server.dir/flags.make
test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o: ../test/zmq_protobuf/server/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/main.cpp.o -c /home/diva2/diva2/test/zmq_protobuf/server/main.cpp

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/zmq_protobuf/server/main.cpp > CMakeFiles/server.dir/main.cpp.i

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/zmq_protobuf/server/main.cpp -o CMakeFiles/server.dir/main.cpp.s

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.requires:

.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.requires

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.provides: test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.requires
	$(MAKE) -f test/zmq_protobuf/server/CMakeFiles/server.dir/build.make test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.provides.build
.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.provides

test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.provides.build: test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o


test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o: test/zmq_protobuf/server/CMakeFiles/server.dir/flags.make
test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o: test/zmq_protobuf/server/message.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/message.pb.cc.o -c /home/diva2/diva2/build/test/zmq_protobuf/server/message.pb.cc

test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/message.pb.cc.i"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/build/test/zmq_protobuf/server/message.pb.cc > CMakeFiles/server.dir/message.pb.cc.i

test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/message.pb.cc.s"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/build/test/zmq_protobuf/server/message.pb.cc -o CMakeFiles/server.dir/message.pb.cc.s

test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.requires:

.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.requires

test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.provides: test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.requires
	$(MAKE) -f test/zmq_protobuf/server/CMakeFiles/server.dir/build.make test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.provides.build
.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.provides

test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.provides.build: test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.cpp.o" \
"CMakeFiles/server.dir/message.pb.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

test/zmq_protobuf/server/server: test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o
test/zmq_protobuf/server/server: test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o
test/zmq_protobuf/server/server: test/zmq_protobuf/server/CMakeFiles/server.dir/build.make
test/zmq_protobuf/server/server: /usr/local/lib/libprotobuf.so
test/zmq_protobuf/server/server: /usr/local/lib/libzmq.so
test/zmq_protobuf/server/server: /usr/local/lib/libprotobuf.so
test/zmq_protobuf/server/server: /usr/local/lib/libzmq.so
test/zmq_protobuf/server/server: test/zmq_protobuf/server/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable server"
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/zmq_protobuf/server/CMakeFiles/server.dir/build: test/zmq_protobuf/server/server

.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/build

test/zmq_protobuf/server/CMakeFiles/server.dir/requires: test/zmq_protobuf/server/CMakeFiles/server.dir/main.cpp.o.requires
test/zmq_protobuf/server/CMakeFiles/server.dir/requires: test/zmq_protobuf/server/CMakeFiles/server.dir/message.pb.cc.o.requires

.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/requires

test/zmq_protobuf/server/CMakeFiles/server.dir/clean:
	cd /home/diva2/diva2/build/test/zmq_protobuf/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/clean

test/zmq_protobuf/server/CMakeFiles/server.dir/depend: test/zmq_protobuf/server/message.pb.cc
test/zmq_protobuf/server/CMakeFiles/server.dir/depend: test/zmq_protobuf/server/message.pb.h
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/test/zmq_protobuf/server /home/diva2/diva2/build /home/diva2/diva2/build/test/zmq_protobuf/server /home/diva2/diva2/build/test/zmq_protobuf/server/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/zmq_protobuf/server/CMakeFiles/server.dir/depend

