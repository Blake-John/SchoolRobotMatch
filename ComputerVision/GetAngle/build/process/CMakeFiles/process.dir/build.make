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
include process/CMakeFiles/process.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include process/CMakeFiles/process.dir/compiler_depend.make

# Include the progress variables for this target.
include process/CMakeFiles/process.dir/progress.make

# Include the compile flags for this target's objects.
include process/CMakeFiles/process.dir/flags.make

process/CMakeFiles/process.dir/src/process.cpp.obj: process/CMakeFiles/process.dir/flags.make
process/CMakeFiles/process.dir/src/process.cpp.obj: process/CMakeFiles/process.dir/includes_CXX.rsp
process/CMakeFiles/process.dir/src/process.cpp.obj: D:/robot-match/ComputerVision/GetAngle/process/src/process.cpp
process/CMakeFiles/process.dir/src/process.cpp.obj: process/CMakeFiles/process.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/robot-match/ComputerVision/GetAngle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object process/CMakeFiles/process.dir/src/process.cpp.obj"
	cd D:/robot-match/ComputerVision/GetAngle/build/process && E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT process/CMakeFiles/process.dir/src/process.cpp.obj -MF CMakeFiles/process.dir/src/process.cpp.obj.d -o CMakeFiles/process.dir/src/process.cpp.obj -c D:/robot-match/ComputerVision/GetAngle/process/src/process.cpp

process/CMakeFiles/process.dir/src/process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/process.dir/src/process.cpp.i"
	cd D:/robot-match/ComputerVision/GetAngle/build/process && E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/robot-match/ComputerVision/GetAngle/process/src/process.cpp > CMakeFiles/process.dir/src/process.cpp.i

process/CMakeFiles/process.dir/src/process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/process.dir/src/process.cpp.s"
	cd D:/robot-match/ComputerVision/GetAngle/build/process && E:/w64devkit/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/robot-match/ComputerVision/GetAngle/process/src/process.cpp -o CMakeFiles/process.dir/src/process.cpp.s

# Object files for target process
process_OBJECTS = \
"CMakeFiles/process.dir/src/process.cpp.obj"

# External object files for target process
process_EXTERNAL_OBJECTS =

process/libprocess.a: process/CMakeFiles/process.dir/src/process.cpp.obj
process/libprocess.a: process/CMakeFiles/process.dir/build.make
process/libprocess.a: process/CMakeFiles/process.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/robot-match/ComputerVision/GetAngle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libprocess.a"
	cd D:/robot-match/ComputerVision/GetAngle/build/process && $(CMAKE_COMMAND) -P CMakeFiles/process.dir/cmake_clean_target.cmake
	cd D:/robot-match/ComputerVision/GetAngle/build/process && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/process.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
process/CMakeFiles/process.dir/build: process/libprocess.a
.PHONY : process/CMakeFiles/process.dir/build

process/CMakeFiles/process.dir/clean:
	cd D:/robot-match/ComputerVision/GetAngle/build/process && $(CMAKE_COMMAND) -P CMakeFiles/process.dir/cmake_clean.cmake
.PHONY : process/CMakeFiles/process.dir/clean

process/CMakeFiles/process.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/robot-match/ComputerVision/GetAngle D:/robot-match/ComputerVision/GetAngle/process D:/robot-match/ComputerVision/GetAngle/build D:/robot-match/ComputerVision/GetAngle/build/process D:/robot-match/ComputerVision/GetAngle/build/process/CMakeFiles/process.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : process/CMakeFiles/process.dir/depend

