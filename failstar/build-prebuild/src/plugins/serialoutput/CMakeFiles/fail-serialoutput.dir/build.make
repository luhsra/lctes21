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
CMAKE_SOURCE_DIR = /home/ae/failstar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ae/failstar/build

# Include any dependencies generated for this target.
include src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/depend.make

# Include the progress variables for this target.
include src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/progress.make

# Include the compile flags for this target's objects.
include src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/flags.make

src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o: src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/flags.make
src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o: ../src/plugins/serialoutput/SerialOutputLogger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o"
	cd /home/ae/failstar/build/src/plugins/serialoutput && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o -c /home/ae/failstar/src/plugins/serialoutput/SerialOutputLogger.cc

src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.i"
	cd /home/ae/failstar/build/src/plugins/serialoutput && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/src/plugins/serialoutput/SerialOutputLogger.cc > CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.i

src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.s"
	cd /home/ae/failstar/build/src/plugins/serialoutput && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/src/plugins/serialoutput/SerialOutputLogger.cc -o CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.s

# Object files for target fail-serialoutput
fail__serialoutput_OBJECTS = \
"CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o"

# External object files for target fail-serialoutput
fail__serialoutput_EXTERNAL_OBJECTS =

lib/libfail-serialoutput.a: src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/SerialOutputLogger.cc.o
lib/libfail-serialoutput.a: src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/build.make
lib/libfail-serialoutput.a: src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libfail-serialoutput.a"
	cd /home/ae/failstar/build/src/plugins/serialoutput && $(CMAKE_COMMAND) -P CMakeFiles/fail-serialoutput.dir/cmake_clean_target.cmake
	cd /home/ae/failstar/build/src/plugins/serialoutput && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fail-serialoutput.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/build: lib/libfail-serialoutput.a

.PHONY : src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/build

src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/clean:
	cd /home/ae/failstar/build/src/plugins/serialoutput && $(CMAKE_COMMAND) -P CMakeFiles/fail-serialoutput.dir/cmake_clean.cmake
.PHONY : src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/clean

src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar/src/plugins/serialoutput /home/ae/failstar/build /home/ae/failstar/build/src/plugins/serialoutput /home/ae/failstar/build/src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/plugins/serialoutput/CMakeFiles/fail-serialoutput.dir/depend

