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
include test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/depend.make

# Include the progress variables for this target.
include test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/progress.make

# Include the compile flags for this target's objects.
include test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/flags.make

test/receiver_fromMobile_proto/sensors.pb.cc: ../test/protobuf/sensors.proto
test/receiver_fromMobile_proto/sensors.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on ../protobuf/sensors.proto"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/local/bin/protoc --cpp_out=/home/diva2/diva2/build/test/receiver_fromMobile_proto -I /home/diva2/diva2/test/protobuf /home/diva2/diva2/test/protobuf/sensors.proto

test/receiver_fromMobile_proto/sensors.pb.h: test/receiver_fromMobile_proto/sensors.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate test/receiver_fromMobile_proto/sensors.pb.h

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/flags.make
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o: ../test/receiver_fromMobile_proto/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/receiverFromMobile.dir/main.cpp.o -c /home/diva2/diva2/test/receiver_fromMobile_proto/main.cpp

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/receiverFromMobile.dir/main.cpp.i"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/receiver_fromMobile_proto/main.cpp > CMakeFiles/receiverFromMobile.dir/main.cpp.i

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/receiverFromMobile.dir/main.cpp.s"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/receiver_fromMobile_proto/main.cpp -o CMakeFiles/receiverFromMobile.dir/main.cpp.s

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.requires:

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.requires

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.provides: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.requires
	$(MAKE) -f test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build.make test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.provides.build
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.provides

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.provides.build: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o


test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/flags.make
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o: ../test/receiver_fromMobile_proto/GpsReceiverThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o -c /home/diva2/diva2/test/receiver_fromMobile_proto/GpsReceiverThread.cpp

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.i"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/receiver_fromMobile_proto/GpsReceiverThread.cpp > CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.i

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.s"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/receiver_fromMobile_proto/GpsReceiverThread.cpp -o CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.s

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.requires:

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.requires

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.provides: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.requires
	$(MAKE) -f test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build.make test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.provides.build
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.provides

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.provides.build: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o


test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/flags.make
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o: ../test/receiver_fromMobile_proto/CamReceiverThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o -c /home/diva2/diva2/test/receiver_fromMobile_proto/CamReceiverThread.cpp

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.i"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/test/receiver_fromMobile_proto/CamReceiverThread.cpp > CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.i

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.s"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/test/receiver_fromMobile_proto/CamReceiverThread.cpp -o CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.s

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.requires:

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.requires

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.provides: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.requires
	$(MAKE) -f test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build.make test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.provides.build
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.provides

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.provides.build: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o


test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/flags.make
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o: test/receiver_fromMobile_proto/sensors.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o -c /home/diva2/diva2/build/test/receiver_fromMobile_proto/sensors.pb.cc

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.i"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/build/test/receiver_fromMobile_proto/sensors.pb.cc > CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.i

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.s"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/build/test/receiver_fromMobile_proto/sensors.pb.cc -o CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.s

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.requires:

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.requires

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.provides: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.requires
	$(MAKE) -f test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build.make test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.provides.build
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.provides

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.provides.build: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o


# Object files for target receiverFromMobile
receiverFromMobile_OBJECTS = \
"CMakeFiles/receiverFromMobile.dir/main.cpp.o" \
"CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o" \
"CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o" \
"CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o"

# External object files for target receiverFromMobile
receiverFromMobile_EXTERNAL_OBJECTS =

test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o
test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o
test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o
test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o
test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build.make
test/receiver_fromMobile_proto/receiverFromMobile: /usr/local/lib/libprotobuf.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/local/lib/libzmq.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/share/c++-mscl/libmscl.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/local/lib/libprotobuf.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/local/lib/libzmq.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/share/c++-mscl/libmscl.so
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
test/receiver_fromMobile_proto/receiverFromMobile: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable receiverFromMobile"
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/receiverFromMobile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build: test/receiver_fromMobile_proto/receiverFromMobile

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/build

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/requires: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/main.cpp.o.requires
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/requires: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/GpsReceiverThread.cpp.o.requires
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/requires: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/CamReceiverThread.cpp.o.requires
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/requires: test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/sensors.pb.cc.o.requires

.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/requires

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/clean:
	cd /home/diva2/diva2/build/test/receiver_fromMobile_proto && $(CMAKE_COMMAND) -P CMakeFiles/receiverFromMobile.dir/cmake_clean.cmake
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/clean

test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/depend: test/receiver_fromMobile_proto/sensors.pb.cc
test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/depend: test/receiver_fromMobile_proto/sensors.pb.h
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/test/receiver_fromMobile_proto /home/diva2/diva2/build /home/diva2/diva2/build/test/receiver_fromMobile_proto /home/diva2/diva2/build/test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/receiver_fromMobile_proto/CMakeFiles/receiverFromMobile.dir/depend

