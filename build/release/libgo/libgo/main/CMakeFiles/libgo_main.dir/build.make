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
include libgo/libgo/main/CMakeFiles/libgo_main.dir/depend.make

# Include the progress variables for this target.
include libgo/libgo/main/CMakeFiles/libgo_main.dir/progress.make

# Include the compile flags for this target's objects.
include libgo/libgo/main/CMakeFiles/libgo_main.dir/flags.make

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o: libgo/libgo/main/CMakeFiles/libgo_main.dir/flags.make
libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o: ../../libgo/libgo/main/libgo_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o"
	cd /root/ming_frame/build/release/libgo/libgo/main && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/libgo_main.dir/libgo_main.cpp.o -c /root/ming_frame/libgo/libgo/main/libgo_main.cpp

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libgo_main.dir/libgo_main.cpp.i"
	cd /root/ming_frame/build/release/libgo/libgo/main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/libgo/libgo/main/libgo_main.cpp > CMakeFiles/libgo_main.dir/libgo_main.cpp.i

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libgo_main.dir/libgo_main.cpp.s"
	cd /root/ming_frame/build/release/libgo/libgo/main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/libgo/libgo/main/libgo_main.cpp -o CMakeFiles/libgo_main.dir/libgo_main.cpp.s

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.requires:
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.requires

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.provides: libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.requires
	$(MAKE) -f libgo/libgo/main/CMakeFiles/libgo_main.dir/build.make libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.provides.build
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.provides

libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.provides.build: libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o

# Object files for target libgo_main
libgo_main_OBJECTS = \
"CMakeFiles/libgo_main.dir/libgo_main.cpp.o"

# External object files for target libgo_main
libgo_main_EXTERNAL_OBJECTS =

lib/liblibgo_main.a: libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o
lib/liblibgo_main.a: libgo/libgo/main/CMakeFiles/libgo_main.dir/build.make
lib/liblibgo_main.a: libgo/libgo/main/CMakeFiles/libgo_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../lib/liblibgo_main.a"
	cd /root/ming_frame/build/release/libgo/libgo/main && $(CMAKE_COMMAND) -P CMakeFiles/libgo_main.dir/cmake_clean_target.cmake
	cd /root/ming_frame/build/release/libgo/libgo/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libgo_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libgo/libgo/main/CMakeFiles/libgo_main.dir/build: lib/liblibgo_main.a
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/build

libgo/libgo/main/CMakeFiles/libgo_main.dir/requires: libgo/libgo/main/CMakeFiles/libgo_main.dir/libgo_main.cpp.o.requires
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/requires

libgo/libgo/main/CMakeFiles/libgo_main.dir/clean:
	cd /root/ming_frame/build/release/libgo/libgo/main && $(CMAKE_COMMAND) -P CMakeFiles/libgo_main.dir/cmake_clean.cmake
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/clean

libgo/libgo/main/CMakeFiles/libgo_main.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/libgo/libgo/main /root/ming_frame/build/release /root/ming_frame/build/release/libgo/libgo/main /root/ming_frame/build/release/libgo/libgo/main/CMakeFiles/libgo_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libgo/libgo/main/CMakeFiles/libgo_main.dir/depend

