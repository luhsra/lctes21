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

# Utility rule file for bochsclean.

# Include the progress variables for this target.
include CMakeFiles/bochsclean.dir/progress.make

CMakeFiles/bochsclean:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[FAIL*] Cleaning all up (clean in bochs)"
	+make -C /home/ae/failstar/simulators/bochs clean
	/usr/bin/cmake -E touch_nocreate /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure || true

bochsclean: CMakeFiles/bochsclean
bochsclean: CMakeFiles/bochsclean.dir/build.make

.PHONY : bochsclean

# Rule to build all files generated by this target.
CMakeFiles/bochsclean.dir/build: bochsclean

.PHONY : CMakeFiles/bochsclean.dir/build

CMakeFiles/bochsclean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bochsclean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bochsclean.dir/clean

CMakeFiles/bochsclean.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar /home/ae/failstar/build /home/ae/failstar/build /home/ae/failstar/build/CMakeFiles/bochsclean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bochsclean.dir/depend
