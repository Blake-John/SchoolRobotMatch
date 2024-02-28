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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/blake/Desktop/robot-match/ComputerVision/V3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug

# Include any dependencies generated for this target.
include ReadColorRange/CMakeFiles/readcolor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ReadColorRange/CMakeFiles/readcolor.dir/compiler_depend.make

# Include the progress variables for this target.
include ReadColorRange/CMakeFiles/readcolor.dir/progress.make

# Include the compile flags for this target's objects.
include ReadColorRange/CMakeFiles/readcolor.dir/flags.make

ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o: ReadColorRange/CMakeFiles/readcolor.dir/flags.make
ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o: /home/blake/Desktop/robot-match/ComputerVision/V3/ReadColorRange/readcolor.cpp
ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o: ReadColorRange/CMakeFiles/readcolor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o"
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o -MF CMakeFiles/readcolor.dir/readcolor.cpp.o.d -o CMakeFiles/readcolor.dir/readcolor.cpp.o -c /home/blake/Desktop/robot-match/ComputerVision/V3/ReadColorRange/readcolor.cpp

ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/readcolor.dir/readcolor.cpp.i"
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blake/Desktop/robot-match/ComputerVision/V3/ReadColorRange/readcolor.cpp > CMakeFiles/readcolor.dir/readcolor.cpp.i

ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/readcolor.dir/readcolor.cpp.s"
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blake/Desktop/robot-match/ComputerVision/V3/ReadColorRange/readcolor.cpp -o CMakeFiles/readcolor.dir/readcolor.cpp.s

# Object files for target readcolor
readcolor_OBJECTS = \
"CMakeFiles/readcolor.dir/readcolor.cpp.o"

# External object files for target readcolor
readcolor_EXTERNAL_OBJECTS =

ReadColorRange/libreadcolor.a: ReadColorRange/CMakeFiles/readcolor.dir/readcolor.cpp.o
ReadColorRange/libreadcolor.a: ReadColorRange/CMakeFiles/readcolor.dir/build.make
ReadColorRange/libreadcolor.a: ReadColorRange/CMakeFiles/readcolor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libreadcolor.a"
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && $(CMAKE_COMMAND) -P CMakeFiles/readcolor.dir/cmake_clean_target.cmake
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readcolor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ReadColorRange/CMakeFiles/readcolor.dir/build: ReadColorRange/libreadcolor.a
.PHONY : ReadColorRange/CMakeFiles/readcolor.dir/build

ReadColorRange/CMakeFiles/readcolor.dir/clean:
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange && $(CMAKE_COMMAND) -P CMakeFiles/readcolor.dir/cmake_clean.cmake
.PHONY : ReadColorRange/CMakeFiles/readcolor.dir/clean

ReadColorRange/CMakeFiles/readcolor.dir/depend:
	cd /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blake/Desktop/robot-match/ComputerVision/V3 /home/blake/Desktop/robot-match/ComputerVision/V3/ReadColorRange /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange /home/blake/Desktop/robot-match/ComputerVision/V3/out/Debug/ReadColorRange/CMakeFiles/readcolor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : ReadColorRange/CMakeFiles/readcolor.dir/depend

