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
include src/CMakeFiles/ming.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ming.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ming.dir/flags.make

src/CMakeFiles/ming.dir/config.cpp.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/config.cpp.o: ../../src/config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/config.cpp.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/config.cpp.o -c /root/ming_frame/src/config.cpp

src/CMakeFiles/ming.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/config.cpp.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/config.cpp > CMakeFiles/ming.dir/config.cpp.i

src/CMakeFiles/ming.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/config.cpp.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/config.cpp -o CMakeFiles/ming.dir/config.cpp.s

src/CMakeFiles/ming.dir/config.cpp.o.requires:
.PHONY : src/CMakeFiles/ming.dir/config.cpp.o.requires

src/CMakeFiles/ming.dir/config.cpp.o.provides: src/CMakeFiles/ming.dir/config.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/config.cpp.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/config.cpp.o.provides

src/CMakeFiles/ming.dir/config.cpp.o.provides.build: src/CMakeFiles/ming.dir/config.cpp.o

src/CMakeFiles/ming.dir/log.cpp.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/log.cpp.o: ../../src/log.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/log.cpp.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/log.cpp.o -c /root/ming_frame/src/log.cpp

src/CMakeFiles/ming.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/log.cpp.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/log.cpp > CMakeFiles/ming.dir/log.cpp.i

src/CMakeFiles/ming.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/log.cpp.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/log.cpp -o CMakeFiles/ming.dir/log.cpp.s

src/CMakeFiles/ming.dir/log.cpp.o.requires:
.PHONY : src/CMakeFiles/ming.dir/log.cpp.o.requires

src/CMakeFiles/ming.dir/log.cpp.o.provides: src/CMakeFiles/ming.dir/log.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/log.cpp.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/log.cpp.o.provides

src/CMakeFiles/ming.dir/log.cpp.o.provides.build: src/CMakeFiles/ming.dir/log.cpp.o

src/CMakeFiles/ming.dir/procmon.cpp.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/procmon.cpp.o: ../../src/procmon.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/procmon.cpp.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/procmon.cpp.o -c /root/ming_frame/src/procmon.cpp

src/CMakeFiles/ming.dir/procmon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/procmon.cpp.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/procmon.cpp > CMakeFiles/ming.dir/procmon.cpp.i

src/CMakeFiles/ming.dir/procmon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/procmon.cpp.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/procmon.cpp -o CMakeFiles/ming.dir/procmon.cpp.s

src/CMakeFiles/ming.dir/procmon.cpp.o.requires:
.PHONY : src/CMakeFiles/ming.dir/procmon.cpp.o.requires

src/CMakeFiles/ming.dir/procmon.cpp.o.provides: src/CMakeFiles/ming.dir/procmon.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/procmon.cpp.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/procmon.cpp.o.provides

src/CMakeFiles/ming.dir/procmon.cpp.o.provides.build: src/CMakeFiles/ming.dir/procmon.cpp.o

src/CMakeFiles/ming.dir/plot.cpp.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/plot.cpp.o: ../../src/plot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/plot.cpp.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/plot.cpp.o -c /root/ming_frame/src/plot.cpp

src/CMakeFiles/ming.dir/plot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/plot.cpp.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/plot.cpp > CMakeFiles/ming.dir/plot.cpp.i

src/CMakeFiles/ming.dir/plot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/plot.cpp.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/plot.cpp -o CMakeFiles/ming.dir/plot.cpp.s

src/CMakeFiles/ming.dir/plot.cpp.o.requires:
.PHONY : src/CMakeFiles/ming.dir/plot.cpp.o.requires

src/CMakeFiles/ming.dir/plot.cpp.o.provides: src/CMakeFiles/ming.dir/plot.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/plot.cpp.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/plot.cpp.o.provides

src/CMakeFiles/ming.dir/plot.cpp.o.provides.build: src/CMakeFiles/ming.dir/plot.cpp.o

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o: ../../src/sudoku/sudoku.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/sudoku/sudoku.cc.o -c /root/ming_frame/src/sudoku/sudoku.cc

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/sudoku/sudoku.cc.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/sudoku/sudoku.cc > CMakeFiles/ming.dir/sudoku/sudoku.cc.i

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/sudoku/sudoku.cc.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/sudoku/sudoku.cc -o CMakeFiles/ming.dir/sudoku/sudoku.cc.s

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.requires:
.PHONY : src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.requires

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.provides: src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.provides

src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.provides.build: src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o

src/CMakeFiles/ming.dir/server_prod.cpp.o: src/CMakeFiles/ming.dir/flags.make
src/CMakeFiles/ming.dir/server_prod.cpp.o: ../../src/server_prod.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/release/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ming.dir/server_prod.cpp.o"
	cd /root/ming_frame/build/release/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -o CMakeFiles/ming.dir/server_prod.cpp.o -c /root/ming_frame/src/server_prod.cpp

src/CMakeFiles/ming.dir/server_prod.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ming.dir/server_prod.cpp.i"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -E /root/ming_frame/src/server_prod.cpp > CMakeFiles/ming.dir/server_prod.cpp.i

src/CMakeFiles/ming.dir/server_prod.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ming.dir/server_prod.cpp.s"
	cd /root/ming_frame/build/release/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -std=c++14 -S /root/ming_frame/src/server_prod.cpp -o CMakeFiles/ming.dir/server_prod.cpp.s

src/CMakeFiles/ming.dir/server_prod.cpp.o.requires:
.PHONY : src/CMakeFiles/ming.dir/server_prod.cpp.o.requires

src/CMakeFiles/ming.dir/server_prod.cpp.o.provides: src/CMakeFiles/ming.dir/server_prod.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ming.dir/build.make src/CMakeFiles/ming.dir/server_prod.cpp.o.provides.build
.PHONY : src/CMakeFiles/ming.dir/server_prod.cpp.o.provides

src/CMakeFiles/ming.dir/server_prod.cpp.o.provides.build: src/CMakeFiles/ming.dir/server_prod.cpp.o

# Object files for target ming
ming_OBJECTS = \
"CMakeFiles/ming.dir/config.cpp.o" \
"CMakeFiles/ming.dir/log.cpp.o" \
"CMakeFiles/ming.dir/procmon.cpp.o" \
"CMakeFiles/ming.dir/plot.cpp.o" \
"CMakeFiles/ming.dir/sudoku/sudoku.cc.o" \
"CMakeFiles/ming.dir/server_prod.cpp.o"

# External object files for target ming
ming_EXTERNAL_OBJECTS =

bin/ming: src/CMakeFiles/ming.dir/config.cpp.o
bin/ming: src/CMakeFiles/ming.dir/log.cpp.o
bin/ming: src/CMakeFiles/ming.dir/procmon.cpp.o
bin/ming: src/CMakeFiles/ming.dir/plot.cpp.o
bin/ming: src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o
bin/ming: src/CMakeFiles/ming.dir/server_prod.cpp.o
bin/ming: src/CMakeFiles/ming.dir/build.make
bin/ming: lib/libmuduo_net_cpp11.a
bin/ming: lib/libmuduo_base_cpp11.a
bin/ming: lib/libmuduo_http.a
bin/ming: lib/liblibgo_main.a
bin/ming: lib/libmuduo_inspect.a
bin/ming: lib/libmuduo_http.a
bin/ming: lib/libmuduo_net_cpp11.a
bin/ming: lib/libmuduo_base_cpp11.a
bin/ming: src/CMakeFiles/ming.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/ming"
	cd /root/ming_frame/build/release/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ming.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/ming.dir/build: bin/ming
.PHONY : src/CMakeFiles/ming.dir/build

src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/config.cpp.o.requires
src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/log.cpp.o.requires
src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/procmon.cpp.o.requires
src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/plot.cpp.o.requires
src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/sudoku/sudoku.cc.o.requires
src/CMakeFiles/ming.dir/requires: src/CMakeFiles/ming.dir/server_prod.cpp.o.requires
.PHONY : src/CMakeFiles/ming.dir/requires

src/CMakeFiles/ming.dir/clean:
	cd /root/ming_frame/build/release/src && $(CMAKE_COMMAND) -P CMakeFiles/ming.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ming.dir/clean

src/CMakeFiles/ming.dir/depend:
	cd /root/ming_frame/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src /root/ming_frame/build/release /root/ming_frame/build/release/src /root/ming_frame/build/release/src/CMakeFiles/ming.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/ming.dir/depend

