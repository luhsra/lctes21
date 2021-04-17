# CMake generated Testfile for 
# Source directory: /home/ae/failstar/src/core/util/capstonedisassembler
# Build directory: /home/ae/failstar/build/src/core/util/capstonedisassembler
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(capstoneDisx86Test "/home/ae/failstar/build/bin/capstoneDisTest" "/home/ae/failstar/src/core/util/capstonedisassembler/testing/x86")
set_tests_properties(capstoneDisx86Test PROPERTIES  _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;23;add_test;/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;0;")
add_test(capstoneDisx86_64Test "/home/ae/failstar/build/bin/capstoneDisTest" "/home/ae/failstar/src/core/util/capstonedisassembler/testing/x86_64")
set_tests_properties(capstoneDisx86_64Test PROPERTIES  _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;24;add_test;/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;0;")
add_test(capstoneDisARMM3Test "/home/ae/failstar/build/bin/capstoneDisTest" "/home/ae/failstar/src/core/util/capstonedisassembler/testing/armm3")
set_tests_properties(capstoneDisARMM3Test PROPERTIES  _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;25;add_test;/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;0;")
add_test(capstoneDisARM9Test "/home/ae/failstar/build/bin/capstoneDisTest" "/home/ae/failstar/src/core/util/capstonedisassembler/testing/arm9")
set_tests_properties(capstoneDisARM9Test PROPERTIES  _BACKTRACE_TRIPLES "/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;26;add_test;/home/ae/failstar/src/core/util/capstonedisassembler/CMakeLists.txt;0;")
