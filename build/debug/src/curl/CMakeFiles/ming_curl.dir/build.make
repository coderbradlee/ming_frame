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
CMAKE_BINARY_DIR = /root/ming_frame/build/debug

# Include any dependencies generated for this target.
include src/curl/CMakeFiles/ming_curl.dir/depend.make

# Include the progress variables for this target.
include src/curl/CMakeFiles/ming_curl.dir/progress.make

# Include the compile flags for this target's objects.
include src/curl/CMakeFiles/ming_curl.dir/flags.make

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o: src/curl/CMakeFiles/ming_curl.dir/flags.make
src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o: ../../src/curl/Curl.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o"
	cd /root/ming_frame/build/debug/src/curl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ming_curl.dir/Curl.cc.o -c /root/ming_frame/src/curl/Curl.cc

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming_curl.dir/Curl.cc.i"
	cd /root/ming_frame/build/debug/src/curl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/curl/Curl.cc > CMakeFiles/ming_curl.dir/Curl.cc.i

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming_curl.dir/Curl.cc.s"
	cd /root/ming_frame/build/debug/src/curl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/curl/Curl.cc -o CMakeFiles/ming_curl.dir/Curl.cc.s

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.requires:
.PHONY : src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.requires

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.provides: src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.requires
	$(MAKE) -f src/curl/CMakeFiles/ming_curl.dir/build.make src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.provides.build
.PHONY : src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.provides

src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.provides.build: src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o

# Object files for target ming_curl
ming_curl_OBJECTS = \
"CMakeFiles/ming_curl.dir/Curl.cc.o"

# External object files for target ming_curl
ming_curl_EXTERNAL_OBJECTS =

lib/libming_curl.a: src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o
lib/libming_curl.a: src/curl/CMakeFiles/ming_curl.dir/build.make
lib/libming_curl.a: src/curl/CMakeFiles/ming_curl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libming_curl.a"
	cd /root/ming_frame/build/debug/src/curl && $(CMAKE_COMMAND) -P CMakeFiles/ming_curl.dir/cmake_clean_target.cmake
	cd /root/ming_frame/build/debug/src/curl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ming_curl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/curl/CMakeFiles/ming_curl.dir/build: lib/libming_curl.a
.PHONY : src/curl/CMakeFiles/ming_curl.dir/build

src/curl/CMakeFiles/ming_curl.dir/requires: src/curl/CMakeFiles/ming_curl.dir/Curl.cc.o.requires
.PHONY : src/curl/CMakeFiles/ming_curl.dir/requires

src/curl/CMakeFiles/ming_curl.dir/clean:
	cd /root/ming_frame/build/debug/src/curl && $(CMAKE_COMMAND) -P CMakeFiles/ming_curl.dir/cmake_clean.cmake
.PHONY : src/curl/CMakeFiles/ming_curl.dir/clean

src/curl/CMakeFiles/ming_curl.dir/depend:
	cd /root/ming_frame/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/curl /root/ming_frame/build/debug /root/ming_frame/build/debug/src/curl /root/ming_frame/build/debug/src/curl/CMakeFiles/ming_curl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/curl/CMakeFiles/ming_curl.dir/depend

