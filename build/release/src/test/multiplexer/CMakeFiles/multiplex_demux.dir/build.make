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
include src/test/multiplexer/CMakeFiles/multiplex_demux.dir/depend.make

# Include the progress variables for this target.
include src/test/multiplexer/CMakeFiles/multiplex_demux.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/multiplexer/CMakeFiles/multiplex_demux.dir/flags.make

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/flags.make
src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o: ../../src/test/multiplexer/demux.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o"
	cd /root/ming_frame/build/release/src/test/multiplexer && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/multiplex_demux.dir/demux.cc.o -c /root/ming_frame/src/test/multiplexer/demux.cc

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiplex_demux.dir/demux.cc.i"
	cd /root/ming_frame/build/release/src/test/multiplexer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/multiplexer/demux.cc > CMakeFiles/multiplex_demux.dir/demux.cc.i

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiplex_demux.dir/demux.cc.s"
	cd /root/ming_frame/build/release/src/test/multiplexer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/multiplexer/demux.cc -o CMakeFiles/multiplex_demux.dir/demux.cc.s

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.requires:
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.requires

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.provides: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.requires
	$(MAKE) -f src/test/multiplexer/CMakeFiles/multiplex_demux.dir/build.make src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.provides.build
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.provides

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.provides.build: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o

# Object files for target multiplex_demux
multiplex_demux_OBJECTS = \
"CMakeFiles/multiplex_demux.dir/demux.cc.o"

# External object files for target multiplex_demux
multiplex_demux_EXTERNAL_OBJECTS =

bin/multiplex_demux: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o
bin/multiplex_demux: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/build.make
bin/multiplex_demux: lib/libmuduo_net_cpp11.a
bin/multiplex_demux: lib/libmuduo_base_cpp11.a
bin/multiplex_demux: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/multiplex_demux"
	cd /root/ming_frame/build/release/src/test/multiplexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multiplex_demux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/multiplexer/CMakeFiles/multiplex_demux.dir/build: bin/multiplex_demux
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/build

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/requires: src/test/multiplexer/CMakeFiles/multiplex_demux.dir/demux.cc.o.requires
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/requires

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/clean:
	cd /root/ming_frame/build/release/src/test/multiplexer && $(CMAKE_COMMAND) -P CMakeFiles/multiplex_demux.dir/cmake_clean.cmake
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/clean

src/test/multiplexer/CMakeFiles/multiplex_demux.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/test/multiplexer /root/ming_frame/build/release /root/ming_frame/build/release/src/test/multiplexer /root/ming_frame/build/release/src/test/multiplexer/CMakeFiles/multiplex_demux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/test/multiplexer/CMakeFiles/multiplex_demux.dir/depend

