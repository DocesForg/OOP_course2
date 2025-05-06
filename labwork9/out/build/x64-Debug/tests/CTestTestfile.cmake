# CMake generated Testfile for 
# Source directory: D:/Desktop/labwork9/tests
# Build directory: D:/Desktop/labwork9/out/build/x64-Debug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("D:/Desktop/labwork9/out/build/x64-Debug/tests/adapter_tests[1]_include.cmake")
add_test([=[adapter_tests]=] "D:/Desktop/labwork9/out/build/x64-Debug/tests/adapter_tests.exe")
set_tests_properties([=[adapter_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Desktop/labwork9/tests/CMakeLists.txt;27;add_test;D:/Desktop/labwork9/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
