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
include src/go/CMakeFiles/sample5_asio.t.dir/depend.make

# Include the progress variables for this target.
include src/go/CMakeFiles/sample5_asio.t.dir/progress.make

# Include the compile flags for this target's objects.
include src/go/CMakeFiles/sample5_asio.t.dir/flags.make

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o: src/go/CMakeFiles/sample5_asio.t.dir/flags.make
src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o: ../../src/go/sample5_asio.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o"
	cd /root/ming_frame/build/debug/src/go && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o -c /root/ming_frame/src/go/sample5_asio.cpp

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.i"
	cd /root/ming_frame/build/debug/src/go && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/go/sample5_asio.cpp > CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.i

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.s"
	cd /root/ming_frame/build/debug/src/go && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/go/sample5_asio.cpp -o CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.s

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.requires:
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.requires

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.provides: src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.requires
	$(MAKE) -f src/go/CMakeFiles/sample5_asio.t.dir/build.make src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.provides.build
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.provides

src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.provides.build: src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o

# Object files for target sample5_asio.t
sample5_asio_t_OBJECTS = \
"CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o"

# External object files for target sample5_asio.t
sample5_asio_t_EXTERNAL_OBJECTS =

bin/sample5_asio.t: src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o
bin/sample5_asio.t: src/go/CMakeFiles/sample5_asio.t.dir/build.make
bin/sample5_asio.t: lib/liblibgo_main.a
bin/sample5_asio.t: src/go/CMakeFiles/sample5_asio.t.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/sample5_asio.t"
	cd /root/ming_frame/build/debug/src/go && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample5_asio.t.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/go/CMakeFiles/sample5_asio.t.dir/build: bin/sample5_asio.t
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/build

src/go/CMakeFiles/sample5_asio.t.dir/requires: src/go/CMakeFiles/sample5_asio.t.dir/sample5_asio.cpp.o.requires
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/requires

src/go/CMakeFiles/sample5_asio.t.dir/clean:
	cd /root/ming_frame/build/debug/src/go && $(CMAKE_COMMAND) -P CMakeFiles/sample5_asio.t.dir/cmake_clean.cmake
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/clean

src/go/CMakeFiles/sample5_asio.t.dir/depend:
	cd /root/ming_frame/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/go /root/ming_frame/build/debug /root/ming_frame/build/debug/src/go /root/ming_frame/build/debug/src/go/CMakeFiles/sample5_asio.t.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/go/CMakeFiles/sample5_asio.t.dir/depend

