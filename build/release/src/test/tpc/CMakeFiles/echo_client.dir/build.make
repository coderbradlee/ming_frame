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
include src/test/tpc/CMakeFiles/echo_client.dir/depend.make

# Include the progress variables for this target.
include src/test/tpc/CMakeFiles/echo_client.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/tpc/CMakeFiles/echo_client.dir/flags.make

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o: src/test/tpc/CMakeFiles/echo_client.dir/flags.make
src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o: ../../src/test/tpc/Acceptor.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/Acceptor.cc.o -c /root/ming_frame/src/test/tpc/Acceptor.cc

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/Acceptor.cc.i"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/tpc/Acceptor.cc > CMakeFiles/echo_client.dir/Acceptor.cc.i

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/Acceptor.cc.s"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/tpc/Acceptor.cc -o CMakeFiles/echo_client.dir/Acceptor.cc.s

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.requires:
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.requires

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.provides: src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.requires
	$(MAKE) -f src/test/tpc/CMakeFiles/echo_client.dir/build.make src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.provides.build
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.provides

src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.provides.build: src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o: src/test/tpc/CMakeFiles/echo_client.dir/flags.make
src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o: ../../src/test/tpc/InetAddress.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/InetAddress.cc.o -c /root/ming_frame/src/test/tpc/InetAddress.cc

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/InetAddress.cc.i"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/tpc/InetAddress.cc > CMakeFiles/echo_client.dir/InetAddress.cc.i

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/InetAddress.cc.s"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/tpc/InetAddress.cc -o CMakeFiles/echo_client.dir/InetAddress.cc.s

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.requires:
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.requires

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.provides: src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.requires
	$(MAKE) -f src/test/tpc/CMakeFiles/echo_client.dir/build.make src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.provides.build
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.provides

src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.provides.build: src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o: src/test/tpc/CMakeFiles/echo_client.dir/flags.make
src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o: ../../src/test/tpc/TcpStream.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/TcpStream.cc.o -c /root/ming_frame/src/test/tpc/TcpStream.cc

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/TcpStream.cc.i"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/tpc/TcpStream.cc > CMakeFiles/echo_client.dir/TcpStream.cc.i

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/TcpStream.cc.s"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/tpc/TcpStream.cc -o CMakeFiles/echo_client.dir/TcpStream.cc.s

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.requires:
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.requires

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.provides: src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.requires
	$(MAKE) -f src/test/tpc/CMakeFiles/echo_client.dir/build.make src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.provides.build
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.provides

src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.provides.build: src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o: src/test/tpc/CMakeFiles/echo_client.dir/flags.make
src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o: ../../src/test/tpc/Socket.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/Socket.cc.o -c /root/ming_frame/src/test/tpc/Socket.cc

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/Socket.cc.i"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/tpc/Socket.cc > CMakeFiles/echo_client.dir/Socket.cc.i

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/Socket.cc.s"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/tpc/Socket.cc -o CMakeFiles/echo_client.dir/Socket.cc.s

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.requires:
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.requires

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.provides: src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.requires
	$(MAKE) -f src/test/tpc/CMakeFiles/echo_client.dir/build.make src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.provides.build
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.provides

src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.provides.build: src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o: src/test/tpc/CMakeFiles/echo_client.dir/flags.make
src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o: ../../src/test/tpc/echo_client.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/echo_client.cc.o -c /root/ming_frame/src/test/tpc/echo_client.cc

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/echo_client.cc.i"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/test/tpc/echo_client.cc > CMakeFiles/echo_client.dir/echo_client.cc.i

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/echo_client.cc.s"
	cd /root/ming_frame/build/release/src/test/tpc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/test/tpc/echo_client.cc -o CMakeFiles/echo_client.dir/echo_client.cc.s

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.requires:
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.requires

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.provides: src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.requires
	$(MAKE) -f src/test/tpc/CMakeFiles/echo_client.dir/build.make src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.provides.build
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.provides

src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.provides.build: src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o

# Object files for target echo_client
echo_client_OBJECTS = \
"CMakeFiles/echo_client.dir/Acceptor.cc.o" \
"CMakeFiles/echo_client.dir/InetAddress.cc.o" \
"CMakeFiles/echo_client.dir/TcpStream.cc.o" \
"CMakeFiles/echo_client.dir/Socket.cc.o" \
"CMakeFiles/echo_client.dir/echo_client.cc.o"

# External object files for target echo_client
echo_client_EXTERNAL_OBJECTS =

bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/build.make
bin/echo_client: src/test/tpc/CMakeFiles/echo_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/echo_client"
	cd /root/ming_frame/build/release/src/test/tpc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/tpc/CMakeFiles/echo_client.dir/build: bin/echo_client
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/build

src/test/tpc/CMakeFiles/echo_client.dir/requires: src/test/tpc/CMakeFiles/echo_client.dir/Acceptor.cc.o.requires
src/test/tpc/CMakeFiles/echo_client.dir/requires: src/test/tpc/CMakeFiles/echo_client.dir/InetAddress.cc.o.requires
src/test/tpc/CMakeFiles/echo_client.dir/requires: src/test/tpc/CMakeFiles/echo_client.dir/TcpStream.cc.o.requires
src/test/tpc/CMakeFiles/echo_client.dir/requires: src/test/tpc/CMakeFiles/echo_client.dir/Socket.cc.o.requires
src/test/tpc/CMakeFiles/echo_client.dir/requires: src/test/tpc/CMakeFiles/echo_client.dir/echo_client.cc.o.requires
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/requires

src/test/tpc/CMakeFiles/echo_client.dir/clean:
	cd /root/ming_frame/build/release/src/test/tpc && $(CMAKE_COMMAND) -P CMakeFiles/echo_client.dir/cmake_clean.cmake
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/clean

src/test/tpc/CMakeFiles/echo_client.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src/test/tpc /root/ming_frame/build/release /root/ming_frame/build/release/src/test/tpc /root/ming_frame/build/release/src/test/tpc/CMakeFiles/echo_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/test/tpc/CMakeFiles/echo_client.dir/depend

