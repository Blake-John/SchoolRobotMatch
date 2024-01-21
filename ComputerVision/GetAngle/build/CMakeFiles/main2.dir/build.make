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
CMAKE_COMMAND = E:/CMake/bin/cmake.exe

# The command to remove a file.
RM = E:/CMake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/robot-match/ComputerVision/GetAngle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/robot-match/ComputerVision/GetAngle/build

# Include any dependencies generated for this target.
include CMakeFiles/main2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main2.dir/flags.make

CMakeFiles/main2.dir/main2.cpp.obj: CMakeFiles/main2.dir/flags.make
CMakeFiles/main2.dir/main2.cpp.obj: CMakeFiles/main2.dir/includes_CXX.rsp
CMakeFiles/main2.dir/main2.cpp.obj: D:/robot-match/ComputerVision/GetAngle/main2.cpp
CMakeFiles/main2.dir/main2.cpp.obj: CMakeFiles/main2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/robot-match/ComputerVision/GetAngle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main2.dir/main2.cpp.obj"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main2.dir/main2.cpp.obj -MF CMakeFiles/main2.dir/main2.cpp.obj.d -o CMakeFiles/main2.dir/main2.cpp.obj -c D:/robot-match/ComputerVision/GetAngle/main2.cpp

CMakeFiles/main2.dir/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main2.dir/main2.cpp.i"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/robot-match/ComputerVision/GetAngle/main2.cpp > CMakeFiles/main2.dir/main2.cpp.i

CMakeFiles/main2.dir/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main2.dir/main2.cpp.s"
	E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/robot-match/ComputerVision/GetAngle/main2.cpp -o CMakeFiles/main2.dir/main2.cpp.s

# Object files for target main2
main2_OBJECTS = \
"CMakeFiles/main2.dir/main2.cpp.obj"

# External object files for target main2
main2_EXTERNAL_OBJECTS =

main2.exe: CMakeFiles/main2.dir/main2.cpp.obj
main2.exe: CMakeFiles/main2.dir/build.make
main2.exe: mathfunc/libmathfunc.a
main2.exe: process/libprocess.a
main2.exe: funcs/libfuncs.a
main2.exe: process/libprocess.a
main2.exe: mathfunc/libmathfunc.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_gapi490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_highgui490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ml490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_objdetect490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_photo490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stitching490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_video490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_calib3d490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_features2d490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_flann490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videoio490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgcodecs490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgproc490.dll.a
main2.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_core490.dll.a
main2.exe: CMakeFiles/main2.dir/linkLibs.rsp
main2.exe: CMakeFiles/main2.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/robot-match/ComputerVision/GetAngle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main2.exe"
	E:/CMake/bin/cmake.exe -E rm -f CMakeFiles/main2.dir/objects.a
	E:/w64devkit/bin/ar.exe qc CMakeFiles/main2.dir/objects.a @CMakeFiles/main2.dir/objects1.rsp
	E:/w64devkit/bin/c++.exe -Wl,--whole-archive CMakeFiles/main2.dir/objects.a -Wl,--no-whole-archive -o main2.exe -Wl,--out-implib,libmain2.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/main2.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/main2.dir/build: main2.exe
.PHONY : CMakeFiles/main2.dir/build

CMakeFiles/main2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main2.dir/clean

CMakeFiles/main2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/robot-match/ComputerVision/GetAngle D:/robot-match/ComputerVision/GetAngle D:/robot-match/ComputerVision/GetAngle/build D:/robot-match/ComputerVision/GetAngle/build D:/robot-match/ComputerVision/GetAngle/build/CMakeFiles/main2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main2.dir/depend

