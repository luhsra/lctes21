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

# Utility rule file for doc.

# Include the progress variables for this target.
include CMakeFiles/doc.dir/progress.make

CMakeFiles/doc: Doxyfile
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[FAIL*] Generating FAIL* documentation with Doxygen"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "       Directories: /home/ae/failstar/src/core/ /home/ae/failstar/src/core/cpn /home/ae/failstar/src/core/config /home/ae/failstar/src/core/util /home/ae/failstar/src/core/util/gzstream /home/ae/failstar/src/core/util/optionparser /home/ae/failstar/src/core/util/capstonedisassembler /home/ae/failstar/src/core/util/capstonedisassembler/testing /home/ae/failstar/src/core/util/testing /home/ae/failstar/src/core/util/smarthops /home/ae/failstar/src/core/util/llvmdisassembler /home/ae/failstar/src/core/util/llvmdisassembler/testing /home/ae/failstar/src/core/sal /home/ae/failstar/src/core/sal/qemu /home/ae/failstar/src/core/sal/x86 /home/ae/failstar/src/core/sal/bochs /home/ae/failstar/src/core/sal/t32 /home/ae/failstar/src/core/sal/gem5 /home/ae/failstar/src/core/sal/panda /home/ae/failstar/src/core/sal/perf /home/ae/failstar/src/core/sal/arm /home/ae/failstar/src/core/efw /home/ae/failstar/src/core/comm  /home/ae/failstar/src/plugins"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "       Excluded patterns: */util/pstream.h */util/optionparser/optionparser.h"
	/usr/bin/doxygen /home/ae/failstar/build/Doxyfile

doc: CMakeFiles/doc
doc: CMakeFiles/doc.dir/build.make

.PHONY : doc

# Rule to build all files generated by this target.
CMakeFiles/doc.dir/build: doc

.PHONY : CMakeFiles/doc.dir/build

CMakeFiles/doc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doc.dir/clean

CMakeFiles/doc.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar /home/ae/failstar/build /home/ae/failstar/build /home/ae/failstar/build/CMakeFiles/doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doc.dir/depend
