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
include test/sensor_connect/CMakeFiles/sensing.dir/depend.make

# Include the progress variables for this target.
include test/sensor_connect/CMakeFiles/sensing.dir/progress.make

# Include the compile flags for this target's objects.
include test/sensor_connect/CMakeFiles/sensing.dir/flags.make

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o: test/sensor_connect/CMakeFiles/sensing.dir/flags.make
test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o: ../test/sensor_connect/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o"
	cd /home/diva2/diva2/build/test/sensor_connect && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensing.dir/main.cpp.o -c /home/diva2/diva2/test/sensor_connect/main.cpp

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensing.dir/main.cpp.i"
	cd /home/diva2/diva2/build/test/sensor_connect && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/sensor_connect/main.cpp > CMakeFiles/sensing.dir/main.cpp.i

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensing.dir/main.cpp.s"
	cd /home/diva2/diva2/build/test/sensor_connect && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/sensor_connect/main.cpp -o CMakeFiles/sensing.dir/main.cpp.s

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.requires:

.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.requires

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.provides: test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.requires
	$(MAKE) -f test/sensor_connect/CMakeFiles/sensing.dir/build.make test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.provides.build
.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.provides

test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.provides.build: test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o


# Object files for target sensing
sensing_OBJECTS = \
"CMakeFiles/sensing.dir/main.cpp.o"

# External object files for target sensing
sensing_EXTERNAL_OBJECTS =

test/sensor_connect/sensing: test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o
test/sensor_connect/sensing: test/sensor_connect/CMakeFiles/sensing.dir/build.make
test/sensor_connect/sensing: /usr/local/lib/libzmq.so
test/sensor_connect/sensing: /usr/share/c++-mscl/libmscl.so
test/sensor_connect/sensing: test/sensor_connect/CMakeFiles/sensing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sensing"
	cd /home/diva2/diva2/build/test/sensor_connect && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sensing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/sensor_connect/CMakeFiles/sensing.dir/build: test/sensor_connect/sensing

.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/build

test/sensor_connect/CMakeFiles/sensing.dir/requires: test/sensor_connect/CMakeFiles/sensing.dir/main.cpp.o.requires

.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/requires

test/sensor_connect/CMakeFiles/sensing.dir/clean:
	cd /home/diva2/diva2/build/test/sensor_connect && $(CMAKE_COMMAND) -P CMakeFiles/sensing.dir/cmake_clean.cmake
.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/clean

test/sensor_connect/CMakeFiles/sensing.dir/depend:
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/test/sensor_connect /home/diva2/diva2/build /home/diva2/diva2/build/test/sensor_connect /home/diva2/diva2/build/test/sensor_connect/CMakeFiles/sensing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/sensor_connect/CMakeFiles/sensing.dir/depend

