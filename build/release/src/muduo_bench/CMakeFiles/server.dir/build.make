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
include src/muduo_bench/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include src/muduo_bench/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/muduo_bench/CMakeFiles/server.dir/flags.make

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o: src/muduo_bench/CMakeFiles/server.dir/flags.make
src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o: ../../src/muduo_bench/pingpong_server.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o"
	cd /root/ming_frame/build/release/src/muduo_bench && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/server.dir/pingpong_server.cc.o -c /root/ming_frame/src/muduo_bench/pingpong_server.cc

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/pingpong_server.cc.i"
	cd /root/ming_frame/build/release/src/muduo_bench && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/muduo_bench/pingpong_server.cc > CMakeFiles/server.dir/pingpong_server.cc.i

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/pingpong_server.cc.s"
	cd /root/ming_frame/build/release/src/muduo_bench && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/muduo_bench/pingpong_server.cc -o CMakeFiles/server.dir/pingpong_server.cc.s

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.requires:
.PHONY : src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.requires

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.provides: src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.requires
	$(MAKE) -f src/muduo_bench/CMakeFiles/server.dir/build.make src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.provides.build
.PHONY : src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.provides

src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.provides.build: src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/pingpong_server.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

bin/server: src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o
bin/server: src/muduo_bench/CMakeFiles/server.dir/build.make
bin/server: lib/libmuduo_net_cpp11.a
bin/server: lib/libmuduo_base_cpp11.a
bin/server: src/muduo_bench/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/server"
	cd /root/ming_frame/build/release/src/muduo_bench && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/muduo_bench/CMakeFiles/server.dir/build: bin/server
.PHONY : src/muduo_bench/CMakeFiles/server.dir/build

src/muduo_bench/CMakeFiles/server.dir/requires: src/muduo_bench/CMakeFiles/server.dir/pingpong_server.cc.o.requires
.PHONY : src/muduo_bench/CMakeFiles/server.dir/requires

src/muduo_bench/CMakeFiles/server.dir/clean:
	cd /root/ming_frame/build/release/src/muduo_bench && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/muduo_bench/CMakeFiles/server.dir/clean

src/muduo_bench/CMakeFiles/server.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/muduo_bench /root/ming_frame/build/release /root/ming_frame/build/release/src/muduo_bench /root/ming_frame/build/release/src/muduo_bench/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/muduo_bench/CMakeFiles/server.dir/depend

