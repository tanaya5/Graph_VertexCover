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
CMAKE_SOURCE_DIR = /home/ttanaya/ece650-a3-tanaya5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ttanaya/ece650-a3-tanaya5/build

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

CMakeFiles/tests.dir/test.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/test.cpp.o: ../test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ttanaya/ece650-a3-tanaya5/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tests.dir/test.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/test.cpp.o -c /home/ttanaya/ece650-a3-tanaya5/test.cpp

CMakeFiles/tests.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/test.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ttanaya/ece650-a3-tanaya5/test.cpp > CMakeFiles/tests.dir/test.cpp.i

CMakeFiles/tests.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ttanaya/ece650-a3-tanaya5/test.cpp -o CMakeFiles/tests.dir/test.cpp.s

CMakeFiles/tests.dir/test.cpp.o.requires:
.PHONY : CMakeFiles/tests.dir/test.cpp.o.requires

CMakeFiles/tests.dir/test.cpp.o.provides: CMakeFiles/tests.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/tests.dir/test.cpp.o.provides

CMakeFiles/tests.dir/test.cpp.o.provides.build: CMakeFiles/tests.dir/test.cpp.o

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/test.cpp.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests.dir/test.cpp.o
tests: CMakeFiles/tests.dir/build.make
tests: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests
.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/requires: CMakeFiles/tests.dir/test.cpp.o.requires
.PHONY : CMakeFiles/tests.dir/requires

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend:
	cd /home/ttanaya/ece650-a3-tanaya5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ttanaya/ece650-a3-tanaya5 /home/ttanaya/ece650-a3-tanaya5 /home/ttanaya/ece650-a3-tanaya5/build /home/ttanaya/ece650-a3-tanaya5/build /home/ttanaya/ece650-a3-tanaya5/build/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests.dir/depend

