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
include src/protobuf/codec/CMakeFiles/protobuf_client.dir/depend.make

# Include the progress variables for this target.
include src/protobuf/codec/CMakeFiles/protobuf_client.dir/progress.make

# Include the compile flags for this target's objects.
include src/protobuf/codec/CMakeFiles/protobuf_client.dir/flags.make

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o: src/protobuf/codec/CMakeFiles/protobuf_client.dir/flags.make
src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o: ../../src/protobuf/codec/client.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o"
	cd /root/ming_frame/build/release/src/protobuf/codec && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -Wno-error=shadow -o CMakeFiles/protobuf_client.dir/client.cc.o -c /root/ming_frame/src/protobuf/codec/client.cc

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/protobuf_client.dir/client.cc.i"
	cd /root/ming_frame/build/release/src/protobuf/codec && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-error=shadow -E /root/ming_frame/src/protobuf/codec/client.cc > CMakeFiles/protobuf_client.dir/client.cc.i

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/protobuf_client.dir/client.cc.s"
	cd /root/ming_frame/build/release/src/protobuf/codec && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-error=shadow -S /root/ming_frame/src/protobuf/codec/client.cc -o CMakeFiles/protobuf_client.dir/client.cc.s

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.requires:
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.requires

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.provides: src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.requires
	$(MAKE) -f src/protobuf/codec/CMakeFiles/protobuf_client.dir/build.make src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.provides.build
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.provides

src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.provides.build: src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o

# Object files for target protobuf_client
protobuf_client_OBJECTS = \
"CMakeFiles/protobuf_client.dir/client.cc.o"

# External object files for target protobuf_client
protobuf_client_EXTERNAL_OBJECTS =

bin/protobuf_client: src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o
bin/protobuf_client: src/protobuf/codec/CMakeFiles/protobuf_client.dir/build.make
bin/protobuf_client: lib/libprotobuf_codec.a
bin/protobuf_client: lib/libquery_proto.a
bin/protobuf_client: lib/libmuduo_net_cpp11.a
bin/protobuf_client: lib/libmuduo_base_cpp11.a
bin/protobuf_client: src/protobuf/codec/CMakeFiles/protobuf_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/protobuf_client"
	cd /root/ming_frame/build/release/src/protobuf/codec && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/protobuf_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/protobuf/codec/CMakeFiles/protobuf_client.dir/build: bin/protobuf_client
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/build

src/protobuf/codec/CMakeFiles/protobuf_client.dir/requires: src/protobuf/codec/CMakeFiles/protobuf_client.dir/client.cc.o.requires
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/requires

src/protobuf/codec/CMakeFiles/protobuf_client.dir/clean:
	cd /root/ming_frame/build/release/src/protobuf/codec && $(CMAKE_COMMAND) -P CMakeFiles/protobuf_client.dir/cmake_clean.cmake
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/clean

src/protobuf/codec/CMakeFiles/protobuf_client.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/protobuf/codec /root/ming_frame/build/release /root/ming_frame/build/release/src/protobuf/codec /root/ming_frame/build/release/src/protobuf/codec/CMakeFiles/protobuf_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/protobuf/codec/CMakeFiles/protobuf_client.dir/depend

