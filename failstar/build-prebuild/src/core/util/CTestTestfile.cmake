# CMake generated Testfile for 
# Source directory: /home/ae/failstar/src/core/util
# Build directory: /home/ae/failstar/build/src/core/util
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(memorymap-test "/home/ae/failstar/build/bin/memorymap-test")
set_tests_properties(memorymap-test PROPERTIES  WORKING_DIRECTORY "/home/ae/failstar/src/core/util/testing" _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/CMakeLists.txt;103;add_test;/home/ae/failstar/src/core/util/CMakeLists.txt;0;")
add_test(sumtree-test "/home/ae/failstar/build/bin/sumtree-test")
set_tests_properties(sumtree-test PROPERTIES  WORKING_DIRECTORY "/home/ae/failstar/src/core/util/testing" _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/CMakeLists.txt;107;add_test;/home/ae/failstar/src/core/util/CMakeLists.txt;0;")
subdirs("capstonedisassembler")
