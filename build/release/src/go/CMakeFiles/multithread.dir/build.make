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
include src/go/CMakeFiles/multithread.dir/depend.make

# Include the progress variables for this target.
include src/go/CMakeFiles/multithread.dir/progress.make

# Include the compile flags for this target's objects.
include src/go/CMakeFiles/multithread.dir/flags.make

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o: src/go/CMakeFiles/multithread.dir/flags.make
src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o: ../../src/go/sample8_multithread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o"
	cd /root/ming_frame/build/release/src/go && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/multithread.dir/sample8_multithread.cpp.o -c /root/ming_frame/src/go/sample8_multithread.cpp

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multithread.dir/sample8_multithread.cpp.i"
	cd /root/ming_frame/build/release/src/go && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/go/sample8_multithread.cpp > CMakeFiles/multithread.dir/sample8_multithread.cpp.i

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multithread.dir/sample8_multithread.cpp.s"
	cd /root/ming_frame/build/release/src/go && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/go/sample8_multithread.cpp -o CMakeFiles/multithread.dir/sample8_multithread.cpp.s

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.requires:
.PHONY : src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.requires

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.provides: src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.requires
	$(MAKE) -f src/go/CMakeFiles/multithread.dir/build.make src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.provides.build
.PHONY : src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.provides

src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.provides.build: src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o

# Object files for target multithread
multithread_OBJECTS = \
"CMakeFiles/multithread.dir/sample8_multithread.cpp.o"

# External object files for target multithread
multithread_EXTERNAL_OBJECTS =

bin/multithread: src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o
bin/multithread: src/go/CMakeFiles/multithread.dir/build.make
bin/multithread: lib/liblibgo_main.a
bin/multithread: src/go/CMakeFiles/multithread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/multithread"
	cd /root/ming_frame/build/release/src/go && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multithread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/go/CMakeFiles/multithread.dir/build: bin/multithread
.PHONY : src/go/CMakeFiles/multithread.dir/build

src/go/CMakeFiles/multithread.dir/requires: src/go/CMakeFiles/multithread.dir/sample8_multithread.cpp.o.requires
.PHONY : src/go/CMakeFiles/multithread.dir/requires

src/go/CMakeFiles/multithread.dir/clean:
	cd /root/ming_frame/build/release/src/go && $(CMAKE_COMMAND) -P CMakeFiles/multithread.dir/cmake_clean.cmake
.PHONY : src/go/CMakeFiles/multithread.dir/clean

src/go/CMakeFiles/multithread.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/go /root/ming_frame/build/release /root/ming_frame/build/release/src/go /root/ming_frame/build/release/src/go/CMakeFiles/multithread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/go/CMakeFiles/multithread.dir/depend

