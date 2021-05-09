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
include MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/depend.make

# Include the progress variables for this target.
include MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/progress.make

# Include the compile flags for this target's objects.
include MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make

MobilePlatform/Sensing/sensors.pb.cc: ../protobuf/sensors.proto
MobilePlatform/Sensing/sensors.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on ../../protobuf/sensors.proto"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/local/bin/protoc --cpp_out=/home/diva2/diva2/build/MobilePlatform/Sensing -I /home/diva2/diva2/protobuf /home/diva2/diva2/protobuf/sensors.proto

MobilePlatform/Sensing/sensors.pb.h: MobilePlatform/Sensing/sensors.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate MobilePlatform/Sensing/sensors.pb.h

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o: ../MobilePlatform/Sensing/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_sensing.dir/main.cpp.o -c /home/diva2/diva2/MobilePlatform/Sensing/main.cpp

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_sensing.dir/main.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Sensing/main.cpp > CMakeFiles/MP_sensing.dir/main.cpp.i

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_sensing.dir/main.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Sensing/main.cpp -o CMakeFiles/MP_sensing.dir/main.cpp.s

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.requires:

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.provides: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.requires
	$(MAKE) -f MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.provides.build
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.provides

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.provides.build: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o


MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o: ../MobilePlatform/Sensing/GpsSensingThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o -c /home/diva2/diva2/MobilePlatform/Sensing/GpsSensingThread.cpp

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Sensing/GpsSensingThread.cpp > CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.i

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Sensing/GpsSensingThread.cpp -o CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.s

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.requires:

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.provides: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.requires
	$(MAKE) -f MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.provides.build
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.provides

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.provides.build: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o


MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o: ../MobilePlatform/Sensing/CamSensingThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o -c /home/diva2/diva2/MobilePlatform/Sensing/CamSensingThread.cpp

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Sensing/CamSensingThread.cpp > CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.i

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Sensing/CamSensingThread.cpp -o CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.s

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.requires:

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.provides: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.requires
	$(MAKE) -f MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.provides.build
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.provides

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.provides.build: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o


MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o: ../MobilePlatform/Sensing/ImuSensingThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o -c /home/diva2/diva2/MobilePlatform/Sensing/ImuSensingThread.cpp

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Sensing/ImuSensingThread.cpp > CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.i

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Sensing/ImuSensingThread.cpp -o CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.s

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.requires:

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.provides: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.requires
	$(MAKE) -f MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.provides.build
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.provides

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.provides.build: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o


MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/flags.make
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o: MobilePlatform/Sensing/sensors.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_sensing.dir/sensors.pb.cc.o -c /home/diva2/diva2/build/MobilePlatform/Sensing/sensors.pb.cc

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_sensing.dir/sensors.pb.cc.i"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/build/MobilePlatform/Sensing/sensors.pb.cc > CMakeFiles/MP_sensing.dir/sensors.pb.cc.i

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_sensing.dir/sensors.pb.cc.s"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/build/MobilePlatform/Sensing/sensors.pb.cc -o CMakeFiles/MP_sensing.dir/sensors.pb.cc.s

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.requires:

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.provides: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.requires
	$(MAKE) -f MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.provides.build
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.provides

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.provides.build: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o


# Object files for target MP_sensing
MP_sensing_OBJECTS = \
"CMakeFiles/MP_sensing.dir/main.cpp.o" \
"CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o" \
"CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o" \
"CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o" \
"CMakeFiles/MP_sensing.dir/sensors.pb.cc.o"

# External object files for target MP_sensing
MP_sensing_EXTERNAL_OBJECTS =

MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build.make
MobilePlatform/Sensing/MP_sensing: /usr/local/lib/libzmq.so
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/local/lib/libprotobuf.so
MobilePlatform/Sensing/MP_sensing: /usr/share/c++-mscl/libmscl.so
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
MobilePlatform/Sensing/MP_sensing: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
MobilePlatform/Sensing/MP_sensing: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable MP_sensing"
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MP_sensing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build: MobilePlatform/Sensing/MP_sensing

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/build

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/main.cpp.o.requires
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/GpsSensingThread.cpp.o.requires
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/CamSensingThread.cpp.o.requires
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/ImuSensingThread.cpp.o.requires
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires: MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/sensors.pb.cc.o.requires

.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/requires

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/clean:
	cd /home/diva2/diva2/build/MobilePlatform/Sensing && $(CMAKE_COMMAND) -P CMakeFiles/MP_sensing.dir/cmake_clean.cmake
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/clean

MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/depend: MobilePlatform/Sensing/sensors.pb.cc
MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/depend: MobilePlatform/Sensing/sensors.pb.h
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/MobilePlatform/Sensing /home/diva2/diva2/build /home/diva2/diva2/build/MobilePlatform/Sensing /home/diva2/diva2/build/MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MobilePlatform/Sensing/CMakeFiles/MP_sensing.dir/depend

