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
include src/test/muduo_net/CMakeFiles/trace_string.dir/depend.make

# Include the progress variables for this target.
include src/test/muduo_net/CMakeFiles/trace_string.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/muduo_net/CMakeFiles/trace_string.dir/flags.make

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o: src/test/muduo_net/CMakeFiles/trace_string.dir/flags.make
src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o: ../../src/test/muduo_net/trace_string.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o"
	cd /root/ming_frame/build/release/src/test/muduo_net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/trace_string.dir/trace_string.cpp.o -c /root/ming_frame/src/test/muduo_net/trace_string.cpp

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trace_string.dir/trace_string.cpp.i"
	cd /root/ming_frame/build/release/src/test/muduo_net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/muduo_net/trace_string.cpp > CMakeFiles/trace_string.dir/trace_string.cpp.i

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trace_string.dir/trace_string.cpp.s"
	cd /root/ming_frame/build/release/src/test/muduo_net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/muduo_net/trace_string.cpp -o CMakeFiles/trace_string.dir/trace_string.cpp.s

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.requires:
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.requires

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.provides: src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.requires
	$(MAKE) -f src/test/muduo_net/CMakeFiles/trace_string.dir/build.make src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.provides.build
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.provides

src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.provides.build: src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o

# Object files for target trace_string
trace_string_OBJECTS = \
"CMakeFiles/trace_string.dir/trace_string.cpp.o"

# External object files for target trace_string
trace_string_EXTERNAL_OBJECTS =

bin/trace_string: src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o
bin/trace_string: src/test/muduo_net/CMakeFiles/trace_string.dir/build.make
bin/trace_string: lib/libmuduo_net_cpp11.a
bin/trace_string: lib/libmuduo_base_cpp11.a
bin/trace_string: lib/libmuduo_http.a
bin/trace_string: lib/libmuduo_inspect.a
bin/trace_string: lib/libmuduo_http.a
bin/trace_string: lib/libmuduo_net_cpp11.a
bin/trace_string: lib/libmuduo_base_cpp11.a
bin/trace_string: src/test/muduo_net/CMakeFiles/trace_string.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/trace_string"
	cd /root/ming_frame/build/release/src/test/muduo_net && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trace_string.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/muduo_net/CMakeFiles/trace_string.dir/build: bin/trace_string
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/build

src/test/muduo_net/CMakeFiles/trace_string.dir/requires: src/test/muduo_net/CMakeFiles/trace_string.dir/trace_string.cpp.o.requires
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/requires

src/test/muduo_net/CMakeFiles/trace_string.dir/clean:
	cd /root/ming_frame/build/release/src/test/muduo_net && $(CMAKE_COMMAND) -P CMakeFiles/trace_string.dir/cmake_clean.cmake
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/clean

src/test/muduo_net/CMakeFiles/trace_string.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/test/muduo_net /root/ming_frame/build/release /root/ming_frame/build/release/src/test/muduo_net /root/ming_frame/build/release/src/test/muduo_net/CMakeFiles/trace_string.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/test/muduo_net/CMakeFiles/trace_string.dir/depend

