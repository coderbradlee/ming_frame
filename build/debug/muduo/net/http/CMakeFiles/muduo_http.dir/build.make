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
include muduo/net/http/CMakeFiles/muduo_http.dir/depend.make

# Include the progress variables for this target.
include muduo/net/http/CMakeFiles/muduo_http.dir/progress.make

# Include the compile flags for this target's objects.
include muduo/net/http/CMakeFiles/muduo_http.dir/flags.make

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o: muduo/net/http/CMakeFiles/muduo_http.dir/flags.make
muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o: ../../muduo/net/http/HttpServer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_http.dir/HttpServer.cc.o -c /root/ming_frame/muduo/net/http/HttpServer.cc

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_http.dir/HttpServer.cc.i"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/muduo/net/http/HttpServer.cc > CMakeFiles/muduo_http.dir/HttpServer.cc.i

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_http.dir/HttpServer.cc.s"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/muduo/net/http/HttpServer.cc -o CMakeFiles/muduo_http.dir/HttpServer.cc.s

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.requires:
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.requires

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.provides: muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.requires
	$(MAKE) -f muduo/net/http/CMakeFiles/muduo_http.dir/build.make muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.provides.build
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.provides

muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.provides.build: muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o: muduo/net/http/CMakeFiles/muduo_http.dir/flags.make
muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o: ../../muduo/net/http/HttpResponse.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_http.dir/HttpResponse.cc.o -c /root/ming_frame/muduo/net/http/HttpResponse.cc

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_http.dir/HttpResponse.cc.i"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/muduo/net/http/HttpResponse.cc > CMakeFiles/muduo_http.dir/HttpResponse.cc.i

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_http.dir/HttpResponse.cc.s"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/muduo/net/http/HttpResponse.cc -o CMakeFiles/muduo_http.dir/HttpResponse.cc.s

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.requires:
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.requires

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.provides: muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.requires
	$(MAKE) -f muduo/net/http/CMakeFiles/muduo_http.dir/build.make muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.provides.build
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.provides

muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.provides.build: muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o: muduo/net/http/CMakeFiles/muduo_http.dir/flags.make
muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o: ../../muduo/net/http/HttpContext.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/build/debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_http.dir/HttpContext.cc.o -c /root/ming_frame/muduo/net/http/HttpContext.cc

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_http.dir/HttpContext.cc.i"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/muduo/net/http/HttpContext.cc > CMakeFiles/muduo_http.dir/HttpContext.cc.i

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_http.dir/HttpContext.cc.s"
	cd /root/ming_frame/build/debug/muduo/net/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/muduo/net/http/HttpContext.cc -o CMakeFiles/muduo_http.dir/HttpContext.cc.s

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.requires:
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.requires

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.provides: muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.requires
	$(MAKE) -f muduo/net/http/CMakeFiles/muduo_http.dir/build.make muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.provides.build
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.provides

muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.provides.build: muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o

# Object files for target muduo_http
muduo_http_OBJECTS = \
"CMakeFiles/muduo_http.dir/HttpServer.cc.o" \
"CMakeFiles/muduo_http.dir/HttpResponse.cc.o" \
"CMakeFiles/muduo_http.dir/HttpContext.cc.o"

# External object files for target muduo_http
muduo_http_EXTERNAL_OBJECTS =

lib/libmuduo_http.a: muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o
lib/libmuduo_http.a: muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o
lib/libmuduo_http.a: muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o
lib/libmuduo_http.a: muduo/net/http/CMakeFiles/muduo_http.dir/build.make
lib/libmuduo_http.a: muduo/net/http/CMakeFiles/muduo_http.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../lib/libmuduo_http.a"
	cd /root/ming_frame/build/debug/muduo/net/http && $(CMAKE_COMMAND) -P CMakeFiles/muduo_http.dir/cmake_clean_target.cmake
	cd /root/ming_frame/build/debug/muduo/net/http && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_http.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
muduo/net/http/CMakeFiles/muduo_http.dir/build: lib/libmuduo_http.a
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/build

muduo/net/http/CMakeFiles/muduo_http.dir/requires: muduo/net/http/CMakeFiles/muduo_http.dir/HttpServer.cc.o.requires
muduo/net/http/CMakeFiles/muduo_http.dir/requires: muduo/net/http/CMakeFiles/muduo_http.dir/HttpResponse.cc.o.requires
muduo/net/http/CMakeFiles/muduo_http.dir/requires: muduo/net/http/CMakeFiles/muduo_http.dir/HttpContext.cc.o.requires
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/requires

muduo/net/http/CMakeFiles/muduo_http.dir/clean:
	cd /root/ming_frame/build/debug/muduo/net/http && $(CMAKE_COMMAND) -P CMakeFiles/muduo_http.dir/cmake_clean.cmake
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/clean

muduo/net/http/CMakeFiles/muduo_http.dir/depend:
	cd /root/ming_frame/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/muduo/net/http /root/ming_frame/build/debug /root/ming_frame/build/debug/muduo/net/http /root/ming_frame/build/debug/muduo/net/http/CMakeFiles/muduo_http.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : muduo/net/http/CMakeFiles/muduo_http.dir/depend

