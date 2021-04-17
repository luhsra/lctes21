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

# Utility rule file for libfailbochs_external.

# Include the progress variables for this target.
include CMakeFiles/libfailbochs_external.dir/progress.make

CMakeFiles/libfailbochs_external: CMakeFiles/libfailbochs_external-complete


CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-install
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-build
CMakeFiles/libfailbochs_external-complete: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'libfailbochs_external'"
	/usr/bin/cmake -E make_directory /home/ae/failstar/build/CMakeFiles
	/usr/bin/cmake -E touch /home/ae/failstar/build/CMakeFiles/libfailbochs_external-complete
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-done

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-install: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'libfailbochs_external'"
	cd /home/ae/failstar/simulators/bochs && /usr/bin/cmake -E echo "[FAIL*] Built libfailbochs.a"
	cd /home/ae/failstar/simulators/bochs && /usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-install

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'libfailbochs_external'"
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/tmp
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src
	/usr/bin/cmake -E make_directory /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'libfailbochs_external'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/tmp/libfailbochs_external-cfgcmd.txt
../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update
../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'libfailbochs_external'"
	cd /home/ae/failstar/simulators/bochs && MAKEFLAGS=\"\" /home/ae/failstar/simulators/bochs/configure --enable-a20-pin --enable-x86-64 --enable-cpu-level=6 --enable-ne2000 --enable-acpi --enable-pci --enable-usb --enable-trace-cache --enable-fast-function-calls --enable-host-specific-asms --enable-disasm --enable-readline --enable-clgd54xx --enable-fpu --enable-vmx=2 --enable-monitor-mwait --enable-cdrom --enable-sb16=linux --enable-gdb-stub --disable-docbook --with-nogui --with-x11 --with-wx --with-sdl --prefix=/home/ae/failstar/simulators/bochs/install
	cd /home/ae/failstar/simulators/bochs && /usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure

../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-build: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ae/failstar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'libfailbochs_external'"
	cd /home/ae/failstar/simulators/bochs && $(MAKE) -C /home/ae/failstar/simulators/bochs "CXX=/home/ae/aspectc++/ag++ -p /home/ae/failstar/src -p /home/ae/failstar/simulators -p /home/ae/failstar/debuggers -p /home/ae/failstar/tools -p /home/ae/failstar/build/src -I/home/ae/failstar/src/core -I/home/ae/failstar/build/src/core -D__NO_MATH_INLINES --c_compiler clang++ --Xcompiler -std=gnu++11 -Wno-narrowing" "LIBTOOL=/bin/sh ./libtool --tag=CXX" libfailbochs.a
	cd /home/ae/failstar/simulators/bochs && /usr/bin/cmake -E touch /home/ae/failstar/simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-build

libfailbochs_external: CMakeFiles/libfailbochs_external
libfailbochs_external: CMakeFiles/libfailbochs_external-complete
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-install
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-mkdir
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-download
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-update
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-patch
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-configure
libfailbochs_external: ../simulators/bochs/src/libfailbochs_external-stamp/libfailbochs_external-build
libfailbochs_external: CMakeFiles/libfailbochs_external.dir/build.make

.PHONY : libfailbochs_external

# Rule to build all files generated by this target.
CMakeFiles/libfailbochs_external.dir/build: libfailbochs_external

.PHONY : CMakeFiles/libfailbochs_external.dir/build

CMakeFiles/libfailbochs_external.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libfailbochs_external.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libfailbochs_external.dir/clean

CMakeFiles/libfailbochs_external.dir/depend:
	cd /home/ae/failstar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ae/failstar /home/ae/failstar /home/ae/failstar/build /home/ae/failstar/build /home/ae/failstar/build/CMakeFiles/libfailbochs_external.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libfailbochs_external.dir/depend
