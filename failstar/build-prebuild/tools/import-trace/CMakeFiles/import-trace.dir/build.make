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
include tools/import-trace/CMakeFiles/import-trace.dir/depend.make

# Include the progress variables for this target.
include tools/import-trace/CMakeFiles/import-trace.dir/progress.make

# Include the compile flags for this target's objects.
include tools/import-trace/CMakeFiles/import-trace.dir/flags.make

tools/import-trace/CMakeFiles/import-trace.dir/main.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/main.cc.o: ../tools/import-trace/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/main.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/main.cc.o -c /home/ae/failstar/tools/import-trace/main.cc

tools/import-trace/CMakeFiles/import-trace.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/main.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/main.cc > CMakeFiles/import-trace.dir/main.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/main.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/main.cc -o CMakeFiles/import-trace.dir/main.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.o: ../tools/import-trace/Importer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/Importer.cc.o -c /home/ae/failstar/tools/import-trace/Importer.cc

tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/Importer.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/Importer.cc > CMakeFiles/import-trace.dir/Importer.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/Importer.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/Importer.cc -o CMakeFiles/import-trace.dir/Importer.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.o: ../tools/import-trace/MemoryImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/MemoryImporter.cc.o -c /home/ae/failstar/tools/import-trace/MemoryImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/MemoryImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/MemoryImporter.cc > CMakeFiles/import-trace.dir/MemoryImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/MemoryImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/MemoryImporter.cc -o CMakeFiles/import-trace.dir/MemoryImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.o: ../tools/import-trace/FullTraceImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/FullTraceImporter.cc.o -c /home/ae/failstar/tools/import-trace/FullTraceImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/FullTraceImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/FullTraceImporter.cc > CMakeFiles/import-trace.dir/FullTraceImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/FullTraceImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/FullTraceImporter.cc -o CMakeFiles/import-trace.dir/FullTraceImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.o: ../tools/import-trace/InstructionImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/InstructionImporter.cc.o -c /home/ae/failstar/tools/import-trace/InstructionImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/InstructionImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/InstructionImporter.cc > CMakeFiles/import-trace.dir/InstructionImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/InstructionImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/InstructionImporter.cc -o CMakeFiles/import-trace.dir/InstructionImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.o: ../tools/import-trace/RegisterImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/RegisterImporter.cc.o -c /home/ae/failstar/tools/import-trace/RegisterImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/RegisterImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/RegisterImporter.cc > CMakeFiles/import-trace.dir/RegisterImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/RegisterImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/RegisterImporter.cc -o CMakeFiles/import-trace.dir/RegisterImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o: ../tools/import-trace/RandomJumpImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o -c /home/ae/failstar/tools/import-trace/RandomJumpImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/RandomJumpImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/RandomJumpImporter.cc > CMakeFiles/import-trace.dir/RandomJumpImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/RandomJumpImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/RandomJumpImporter.cc -o CMakeFiles/import-trace.dir/RandomJumpImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o: ../tools/import-trace/AdvancedMemoryImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o -c /home/ae/failstar/tools/import-trace/AdvancedMemoryImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/AdvancedMemoryImporter.cc > CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/AdvancedMemoryImporter.cc -o CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.s

tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.o: tools/import-trace/CMakeFiles/import-trace.dir/flags.make
tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.o: ../tools/import-trace/ElfImporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.o"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/import-trace.dir/ElfImporter.cc.o -c /home/ae/failstar/tools/import-trace/ElfImporter.cc

tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/import-trace.dir/ElfImporter.cc.i"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ae/failstar/tools/import-trace/ElfImporter.cc > CMakeFiles/import-trace.dir/ElfImporter.cc.i

tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/import-trace.dir/ElfImporter.cc.s"
	cd /home/ae/failstar/build/tools/import-trace && /home/ae/aspectc++/ag++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ae/failstar/tools/import-trace/ElfImporter.cc -o CMakeFiles/import-trace.dir/ElfImporter.cc.s

# Object files for target import-trace
import__trace_OBJECTS = \
"CMakeFiles/import-trace.dir/main.cc.o" \
"CMakeFiles/import-trace.dir/Importer.cc.o" \
"CMakeFiles/import-trace.dir/MemoryImporter.cc.o" \
"CMakeFiles/import-trace.dir/FullTraceImporter.cc.o" \
"CMakeFiles/import-trace.dir/InstructionImporter.cc.o" \
"CMakeFiles/import-trace.dir/RegisterImporter.cc.o" \
"CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o" \
"CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o" \
"CMakeFiles/import-trace.dir/ElfImporter.cc.o"

# External object files for target import-trace
import__trace_EXTERNAL_OBJECTS =

bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/main.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/Importer.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/MemoryImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/FullTraceImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/InstructionImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/RegisterImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/RandomJumpImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/AdvancedMemoryImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/ElfImporter.cc.o
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/build.make
bin/import-trace: lib/libfail-util.a
bin/import-trace: lib/libfail-comm.a
bin/import-trace: lib/libfail-sal.a
bin/import-trace: lib/libfail-capstonedisassembler.a
bin/import-trace: lib/libfail-sal.a
bin/import-trace: lib/libfail-efw.a
bin/import-trace: lib/libfail-generic-tracing.a
bin/import-trace: lib/libfail-tracing.a
bin/import-trace: lib/libfail-cpn.a
bin/import-trace: lib/libfail-util.a
bin/import-trace: lib/libfail-sal.a
bin/import-trace: lib/libfail-efw.a
bin/import-trace: lib/libfail-generic-tracing.a
bin/import-trace: lib/libfail-tracing.a
bin/import-trace: lib/libfail-cpn.a
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libiberty.a
bin/import-trace: /usr/lib/x86_64-linux-gnu/libz.so
bin/import-trace: /usr/lib/x86_64-linux-gnu/libdwarf.so
bin/import-trace: /usr/lib/x86_64-linux-gnu/libelf.so
bin/import-trace: lib/libfail-capstonedisassembler.a
bin/import-trace: /usr/local/lib/libcapstone.so
bin/import-trace: /usr/lib/x86_64-linux-gnu/libpcl.so
bin/import-trace: lib/libfail-serialoutput.a
bin/import-trace: lib/libfail-comm.a
bin/import-trace: /usr/lib/x86_64-linux-gnu/libprotobuf.so
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_coroutine.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
bin/import-trace: /usr/lib/x86_64-linux-gnu/libboost_context.so.1.71.0
bin/import-trace: tools/import-trace/CMakeFiles/import-trace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../../bin/import-trace"
	cd /home/ae/failstar/build/tools/import-trace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/import-trace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/import-trace/CMakeFiles/import-trace.dir/build: bin/import-trace

.PHONY : tools/import-trace/CMakeFiles/import-trace.dir/build

tools/import-trace/CMakeFiles/import-trace.dir/clean:
	cd /home/ae/failstar/build/tools/import-trace && $(CMAKE_COMMAND) -P CMakeFiles/import-trace.dir/cmake_clean.cmake
.PHONY : tools/import-trace/CMakeFiles/import-trace.dir/clean

tools/import-trace/CMakeFiles/import-trace.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar/tools/import-trace /home/ae/failstar/build /home/ae/failstar/build/tools/import-trace /home/ae/failstar/build/tools/import-trace/CMakeFiles/import-trace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/import-trace/CMakeFiles/import-trace.dir/depend
