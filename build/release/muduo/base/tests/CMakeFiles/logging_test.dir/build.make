# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ming_frame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ming_frame/build/release

# Include any dependencies generated for this target.
include muduo/base/tests/CMakeFiles/logging_test.dir/depend.make

# Include the progress variables for this target.
include muduo/base/tests/CMakeFiles/logging_test.dir/progress.make

# Include the compile flags for this target's objects.
include muduo/base/tests/CMakeFiles/logging_test.dir/flags.make

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o: muduo/base/tests/CMakeFiles/logging_test.dir/flags.make
muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o: ../../muduo/base/tests/Logging_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o"
	cd /root/ming_frame/build/release/muduo/base/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/logging_test.dir/Logging_test.cc.o -c /root/ming_frame/muduo/base/tests/Logging_test.cc

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logging_test.dir/Logging_test.cc.i"
	cd /root/ming_frame/build/release/muduo/base/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/muduo/base/tests/Logging_test.cc > CMakeFiles/logging_test.dir/Logging_test.cc.i

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logging_test.dir/Logging_test.cc.s"
	cd /root/ming_frame/build/release/muduo/base/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/muduo/base/tests/Logging_test.cc -o CMakeFiles/logging_test.dir/Logging_test.cc.s

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.requires:
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.requires

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.provides: muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.requires
	$(MAKE) -f muduo/base/tests/CMakeFiles/logging_test.dir/build.make muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.provides.build
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.provides

muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.provides.build: muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o

# Object files for target logging_test
logging_test_OBJECTS = \
"CMakeFiles/logging_test.dir/Logging_test.cc.o"

# External object files for target logging_test
logging_test_EXTERNAL_OBJECTS =

bin/logging_test: muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o
bin/logging_test: muduo/base/tests/CMakeFiles/logging_test.dir/build.make
bin/logging_test: lib/libmuduo_base_cpp11.a
bin/logging_test: muduo/base/tests/CMakeFiles/logging_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/logging_test"
	cd /root/ming_frame/build/release/muduo/base/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logging_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
muduo/base/tests/CMakeFiles/logging_test.dir/build: bin/logging_test
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/build

muduo/base/tests/CMakeFiles/logging_test.dir/requires: muduo/base/tests/CMakeFiles/logging_test.dir/Logging_test.cc.o.requires
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/requires

muduo/base/tests/CMakeFiles/logging_test.dir/clean:
	cd /root/ming_frame/build/release/muduo/base/tests && $(CMAKE_COMMAND) -P CMakeFiles/logging_test.dir/cmake_clean.cmake
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/clean

muduo/base/tests/CMakeFiles/logging_test.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/muduo/base/tests /root/ming_frame/build/release /root/ming_frame/build/release/muduo/base/tests /root/ming_frame/build/release/muduo/base/tests/CMakeFiles/logging_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : muduo/base/tests/CMakeFiles/logging_test.dir/depend

