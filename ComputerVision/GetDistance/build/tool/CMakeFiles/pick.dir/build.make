# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/blake/桌面/RobotMatch/ComputerVision/GetDistance

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build

# Include any dependencies generated for this target.
include tool/CMakeFiles/pick.dir/depend.make

# Include the progress variables for this target.
include tool/CMakeFiles/pick.dir/progress.make

# Include the compile flags for this target's objects.
include tool/CMakeFiles/pick.dir/flags.make

tool/CMakeFiles/pick.dir/pick.cpp.o: tool/CMakeFiles/pick.dir/flags.make
tool/CMakeFiles/pick.dir/pick.cpp.o: ../tool/pick.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tool/CMakeFiles/pick.dir/pick.cpp.o"
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pick.dir/pick.cpp.o -c /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/tool/pick.cpp

tool/CMakeFiles/pick.dir/pick.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pick.dir/pick.cpp.i"
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/tool/pick.cpp > CMakeFiles/pick.dir/pick.cpp.i

tool/CMakeFiles/pick.dir/pick.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pick.dir/pick.cpp.s"
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/tool/pick.cpp -o CMakeFiles/pick.dir/pick.cpp.s

# Object files for target pick
pick_OBJECTS = \
"CMakeFiles/pick.dir/pick.cpp.o"

# External object files for target pick
pick_EXTERNAL_OBJECTS =

tool/pick: tool/CMakeFiles/pick.dir/pick.cpp.o
tool/pick: tool/CMakeFiles/pick.dir/build.make
tool/pick: /usr/local/lib/libopencv_highgui.so.4.7.0
tool/pick: /usr/local/lib/libopencv_ml.so.4.7.0
tool/pick: /usr/local/lib/libopencv_objdetect.so.4.7.0
tool/pick: /usr/local/lib/libopencv_photo.so.4.7.0
tool/pick: /usr/local/lib/libopencv_stitching.so.4.7.0
tool/pick: /usr/local/lib/libopencv_video.so.4.7.0
tool/pick: /usr/local/lib/libopencv_videoio.so.4.7.0
tool/pick: /usr/local/lib/libopencv_imgcodecs.so.4.7.0
tool/pick: /usr/local/lib/libopencv_calib3d.so.4.7.0
tool/pick: /usr/local/lib/libopencv_dnn.so.4.7.0
tool/pick: /usr/local/lib/libopencv_features2d.so.4.7.0
tool/pick: /usr/local/lib/libopencv_flann.so.4.7.0
tool/pick: /usr/local/lib/libopencv_imgproc.so.4.7.0
tool/pick: /usr/local/lib/libopencv_core.so.4.7.0
tool/pick: tool/CMakeFiles/pick.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pick"
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pick.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tool/CMakeFiles/pick.dir/build: tool/pick

.PHONY : tool/CMakeFiles/pick.dir/build

tool/CMakeFiles/pick.dir/clean:
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool && $(CMAKE_COMMAND) -P CMakeFiles/pick.dir/cmake_clean.cmake
.PHONY : tool/CMakeFiles/pick.dir/clean

tool/CMakeFiles/pick.dir/depend:
	cd /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blake/桌面/RobotMatch/ComputerVision/GetDistance /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/tool /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool /home/blake/桌面/RobotMatch/ComputerVision/GetDistance/build/tool/CMakeFiles/pick.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tool/CMakeFiles/pick.dir/depend
