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
include MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/depend.make

# Include the progress variables for this target.
include MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/progress.make

# Include the compile flags for this target's objects.
include MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/flags.make

MobilePlatform/Visualization/sensors.pb.cc: ../protobuf/sensors.proto
MobilePlatform/Visualization/sensors.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on ../../protobuf/sensors.proto"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/local/bin/protoc --cpp_out=/home/diva2/diva2/build/MobilePlatform/Visualization -I /home/diva2/diva2/protobuf /home/diva2/diva2/protobuf/sensors.proto

MobilePlatform/Visualization/sensors.pb.h: MobilePlatform/Visualization/sensors.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate MobilePlatform/Visualization/sensors.pb.h

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/flags.make
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o: ../MobilePlatform/Visualization/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_visualization.dir/main.cpp.o -c /home/diva2/diva2/MobilePlatform/Visualization/main.cpp

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_visualization.dir/main.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Visualization/main.cpp > CMakeFiles/MP_visualization.dir/main.cpp.i

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_visualization.dir/main.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Visualization/main.cpp -o CMakeFiles/MP_visualization.dir/main.cpp.s

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.requires:

.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.requires

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.provides: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.requires
	$(MAKE) -f MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build.make MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.provides.build
.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.provides

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.provides.build: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o


MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/flags.make
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o: ../MobilePlatform/Visualization/GpsVisualization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o -c /home/diva2/diva2/MobilePlatform/Visualization/GpsVisualization.cpp

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.i"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/MobilePlatform/Visualization/GpsVisualization.cpp > CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.i

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.s"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/MobilePlatform/Visualization/GpsVisualization.cpp -o CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.s

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.requires:

.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.requires

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.provides: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.requires
	$(MAKE) -f MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build.make MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.provides.build
.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.provides

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.provides.build: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o


MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/flags.make
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o: MobilePlatform/Visualization/sensors.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MP_visualization.dir/sensors.pb.cc.o -c /home/diva2/diva2/build/MobilePlatform/Visualization/sensors.pb.cc

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP_visualization.dir/sensors.pb.cc.i"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diva2/diva2/build/MobilePlatform/Visualization/sensors.pb.cc > CMakeFiles/MP_visualization.dir/sensors.pb.cc.i

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP_visualization.dir/sensors.pb.cc.s"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diva2/diva2/build/MobilePlatform/Visualization/sensors.pb.cc -o CMakeFiles/MP_visualization.dir/sensors.pb.cc.s

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.requires:

.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.requires

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.provides: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.requires
	$(MAKE) -f MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build.make MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.provides.build
.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.provides

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.provides.build: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o


# Object files for target MP_visualization
MP_visualization_OBJECTS = \
"CMakeFiles/MP_visualization.dir/main.cpp.o" \
"CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o" \
"CMakeFiles/MP_visualization.dir/sensors.pb.cc.o"

# External object files for target MP_visualization
MP_visualization_EXTERNAL_OBJECTS =

MobilePlatform/Visualization/MP_visualization: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o
MobilePlatform/Visualization/MP_visualization: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o
MobilePlatform/Visualization/MP_visualization: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o
MobilePlatform/Visualization/MP_visualization: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build.make
MobilePlatform/Visualization/MP_visualization: /usr/local/lib/libzmq.so
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/local/lib/libprotobuf.so
MobilePlatform/Visualization/MP_visualization: /usr/share/c++-mscl/libmscl.so
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
MobilePlatform/Visualization/MP_visualization: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
MobilePlatform/Visualization/MP_visualization: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diva2/diva2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable MP_visualization"
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MP_visualization.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build: MobilePlatform/Visualization/MP_visualization

.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/build

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/requires: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/main.cpp.o.requires
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/requires: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/GpsVisualization.cpp.o.requires
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/requires: MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/sensors.pb.cc.o.requires

.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/requires

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/clean:
	cd /home/diva2/diva2/build/MobilePlatform/Visualization && $(CMAKE_COMMAND) -P CMakeFiles/MP_visualization.dir/cmake_clean.cmake
.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/clean

MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/depend: MobilePlatform/Visualization/sensors.pb.cc
MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/depend: MobilePlatform/Visualization/sensors.pb.h
	cd /home/diva2/diva2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diva2/diva2 /home/diva2/diva2/MobilePlatform/Visualization /home/diva2/diva2/build /home/diva2/diva2/build/MobilePlatform/Visualization /home/diva2/diva2/build/MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MobilePlatform/Visualization/CMakeFiles/MP_visualization.dir/depend

