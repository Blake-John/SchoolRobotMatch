# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = E:/Anaconda/Lib/site-packages/cmake/data/bin/cmake.exe

# The command to remove a file.
RM = E:/Anaconda/Lib/site-packages/cmake/data/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/robot-match/ComputerVision/Calibration/shoot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/robot-match/ComputerVision/Calibration/shoot/build

# Include any dependencies generated for this target.
include CMakeFiles/shoot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shoot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shoot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shoot.dir/flags.make

CMakeFiles/shoot.dir/shoot.cpp.obj: CMakeFiles/shoot.dir/flags.make
CMakeFiles/shoot.dir/shoot.cpp.obj: CMakeFiles/shoot.dir/includes_CXX.rsp
CMakeFiles/shoot.dir/shoot.cpp.obj: D:/robot-match/ComputerVision/Calibration/shoot/shoot.cpp
CMakeFiles/shoot.dir/shoot.cpp.obj: CMakeFiles/shoot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/robot-match/ComputerVision/Calibration/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/shoot.dir/shoot.cpp.obj"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/shoot.dir/shoot.cpp.obj -MF CMakeFiles/shoot.dir/shoot.cpp.obj.d -o CMakeFiles/shoot.dir/shoot.cpp.obj -c D:/robot-match/ComputerVision/Calibration/shoot/shoot.cpp

CMakeFiles/shoot.dir/shoot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/shoot.dir/shoot.cpp.i"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/robot-match/ComputerVision/Calibration/shoot/shoot.cpp > CMakeFiles/shoot.dir/shoot.cpp.i

CMakeFiles/shoot.dir/shoot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/shoot.dir/shoot.cpp.s"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/robot-match/ComputerVision/Calibration/shoot/shoot.cpp -o CMakeFiles/shoot.dir/shoot.cpp.s

# Object files for target shoot
shoot_OBJECTS = \
"CMakeFiles/shoot.dir/shoot.cpp.obj"

# External object files for target shoot
shoot_EXTERNAL_OBJECTS =

shoot.exe: CMakeFiles/shoot.dir/shoot.cpp.obj
shoot.exe: CMakeFiles/shoot.dir/build.make
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_gapi490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_highgui490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ml490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_objdetect490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_photo490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stitching490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_video490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videoio490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgcodecs490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_calib3d490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_features2d490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_flann490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgproc490.dll.a
shoot.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_core490.dll.a
shoot.exe: CMakeFiles/shoot.dir/linkLibs.rsp
shoot.exe: CMakeFiles/shoot.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/robot-match/ComputerVision/Calibration/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable shoot.exe"
	E:/Anaconda/Lib/site-packages/cmake/data/bin/cmake.exe -E rm -f CMakeFiles/shoot.dir/objects.a
	E:/w64devkit/bin/ar.exe qc CMakeFiles/shoot.dir/objects.a @CMakeFiles/shoot.dir/objects1.rsp
	E:/w64devkit/bin/c++.exe -Wl,--whole-archive CMakeFiles/shoot.dir/objects.a -Wl,--no-whole-archive -o shoot.exe -Wl,--out-implib,libshoot.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/shoot.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/shoot.dir/build: shoot.exe
.PHONY : CMakeFiles/shoot.dir/build

CMakeFiles/shoot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shoot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shoot.dir/clean

CMakeFiles/shoot.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/robot-match/ComputerVision/Calibration/shoot D:/robot-match/ComputerVision/Calibration/shoot D:/robot-match/ComputerVision/Calibration/shoot/build D:/robot-match/ComputerVision/Calibration/shoot/build D:/robot-match/ComputerVision/Calibration/shoot/build/CMakeFiles/shoot.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/shoot.dir/depend
