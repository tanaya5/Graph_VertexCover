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
CMAKE_SOURCE_DIR = /home/ttanaya/ece650-project-eceproject650group3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ttanaya/ece650-project-eceproject650group3/build

# Include any dependencies generated for this target.
include CMakeFiles/ece650-prj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ece650-prj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ece650-prj.dir/flags.make

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o: CMakeFiles/ece650-prj.dir/flags.make
CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o: ../ece650-prj.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ttanaya/ece650-project-eceproject650group3/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o -c /home/ttanaya/ece650-project-eceproject650group3/ece650-prj.cpp

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ece650-prj.dir/ece650-prj.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ttanaya/ece650-project-eceproject650group3/ece650-prj.cpp > CMakeFiles/ece650-prj.dir/ece650-prj.cpp.i

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ece650-prj.dir/ece650-prj.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ttanaya/ece650-project-eceproject650group3/ece650-prj.cpp -o CMakeFiles/ece650-prj.dir/ece650-prj.cpp.s

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.requires:
.PHONY : CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.requires

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.provides: CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.requires
	$(MAKE) -f CMakeFiles/ece650-prj.dir/build.make CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.provides.build
.PHONY : CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.provides

CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.provides.build: CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o

# Object files for target ece650-prj
ece650__prj_OBJECTS = \
"CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o"

# External object files for target ece650-prj
ece650__prj_EXTERNAL_OBJECTS =

ece650-prj: CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o
ece650-prj: CMakeFiles/ece650-prj.dir/build.make
ece650-prj: minisat/libminisat.a
ece650-prj: /usr/lib64/libz.so
ece650-prj: CMakeFiles/ece650-prj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ece650-prj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ece650-prj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ece650-prj.dir/build: ece650-prj
.PHONY : CMakeFiles/ece650-prj.dir/build

CMakeFiles/ece650-prj.dir/requires: CMakeFiles/ece650-prj.dir/ece650-prj.cpp.o.requires
.PHONY : CMakeFiles/ece650-prj.dir/requires

CMakeFiles/ece650-prj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ece650-prj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ece650-prj.dir/clean

CMakeFiles/ece650-prj.dir/depend:
	cd /home/ttanaya/ece650-project-eceproject650group3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ttanaya/ece650-project-eceproject650group3 /home/ttanaya/ece650-project-eceproject650group3 /home/ttanaya/ece650-project-eceproject650group3/build /home/ttanaya/ece650-project-eceproject650group3/build /home/ttanaya/ece650-project-eceproject650group3/build/CMakeFiles/ece650-prj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ece650-prj.dir/depend
