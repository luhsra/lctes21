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

# Utility rule file for libfailbochs_external-configure.

# Include the progress variables for this target.
include CMakeFiles/libfailbochs_external-configure.dir/progress.make

CMakeFiles/libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure


../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/tmp/libfailbochs_external-cfgcmd.txt
../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update
../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Performing configure step for 'libfailbochs_external'"
	cd /home/ae/failstar/simulators/bochs && MAKEFLAGS=\"\" /home/ae/failstar/simulators/bochs/configure --enable-a20-pin --enable-x86-64 --enable-cpu-level=6 --enable-ne2000 --enable-acpi --enable-pci --enable-usb --enable-trace-cache --enable-fast-function-calls --enable-host-specific-asms --enable-disasm --enable-readline --enable-clgd54xx --enable-fpu --enable-vmx=2 --enable-monitor-mwait --enable-cdrom --enable-sb16=linux --enable-gdb-stub --disable-docbook --with-nogui --with-x11 --with-wx --with-sdl --prefix=/home/ae/failstar/simulators/bochs/install
	cd /home/ae/failstar/simulators/bochs && /usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No update step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No patch step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Creating directories for 'libfailbochs_external'"
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/tmp
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir

libfailbochs_external-configure: CMakeFiles/libfailbochs_external-configure
libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure
libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update
libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch
libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir
libfailbochs_external-configure: CMakeFiles/libfailbochs_external-configure.dir/build.make

.PHONY : libfailbochs_external-configure

# Rule to build all files generated by this target.
CMakeFiles/libfailbochs_external-configure.dir/build: libfailbochs_external-configure

.PHONY : CMakeFiles/libfailbochs_external-configure.dir/build

CMakeFiles/libfailbochs_external-configure.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libfailbochs_external-configure.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libfailbochs_external-configure.dir/clean

CMakeFiles/libfailbochs_external-configure.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar /home/ae/failstar/build /home/ae/failstar/build /home/ae/failstar/build/CMakeFiles/libfailbochs_external-configure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libfailbochs_external-configure.dir/depend
