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
CMAKE_SOURCE_DIR = /home/ttanaya/ece650-a4-tanaya5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ttanaya/ece650-a4-tanaya5/build

# Include any dependencies generated for this target.
include minisat/CMakeFiles/minisat_simp.dir/depend.make

# Include the progress variables for this target.
include minisat/CMakeFiles/minisat_simp.dir/progress.make

# Include the compile flags for this target's objects.
include minisat/CMakeFiles/minisat_simp.dir/flags.make

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o: minisat/CMakeFiles/minisat_simp.dir/flags.make
minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o: ../minisat/minisat/simp/Main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ttanaya/ece650-a4-tanaya5/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o"
	cd /home/ttanaya/ece650-a4-tanaya5/build/minisat && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o -c /home/ttanaya/ece650-a4-tanaya5/minisat/minisat/simp/Main.cc

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.i"
	cd /home/ttanaya/ece650-a4-tanaya5/build/minisat && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ttanaya/ece650-a4-tanaya5/minisat/minisat/simp/Main.cc > CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.i

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.s"
	cd /home/ttanaya/ece650-a4-tanaya5/build/minisat && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ttanaya/ece650-a4-tanaya5/minisat/minisat/simp/Main.cc -o CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.s

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.requires:
.PHONY : minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.requires

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.provides: minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.requires
	$(MAKE) -f minisat/CMakeFiles/minisat_simp.dir/build.make minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.provides.build
.PHONY : minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.provides

minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.provides.build: minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o

# Object files for target minisat_simp
minisat_simp_OBJECTS = \
"CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o"

# External object files for target minisat_simp
minisat_simp_EXTERNAL_OBJECTS =

minisat/minisat: minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o
minisat/minisat: minisat/CMakeFiles/minisat_simp.dir/build.make
minisat/minisat: minisat/libminisat.a
minisat/minisat: /usr/lib64/libz.so
minisat/minisat: minisat/CMakeFiles/minisat_simp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable minisat"
	cd /home/ttanaya/ece650-a4-tanaya5/build/minisat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minisat_simp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
minisat/CMakeFiles/minisat_simp.dir/build: minisat/minisat
.PHONY : minisat/CMakeFiles/minisat_simp.dir/build

minisat/CMakeFiles/minisat_simp.dir/requires: minisat/CMakeFiles/minisat_simp.dir/minisat/simp/Main.cc.o.requires
.PHONY : minisat/CMakeFiles/minisat_simp.dir/requires

minisat/CMakeFiles/minisat_simp.dir/clean:
	cd /home/ttanaya/ece650-a4-tanaya5/build/minisat && $(CMAKE_COMMAND) -P CMakeFiles/minisat_simp.dir/cmake_clean.cmake
.PHONY : minisat/CMakeFiles/minisat_simp.dir/clean

minisat/CMakeFiles/minisat_simp.dir/depend:
	cd /home/ttanaya/ece650-a4-tanaya5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ttanaya/ece650-a4-tanaya5 /home/ttanaya/ece650-a4-tanaya5/minisat /home/ttanaya/ece650-a4-tanaya5/build /home/ttanaya/ece650-a4-tanaya5/build/minisat /home/ttanaya/ece650-a4-tanaya5/build/minisat/CMakeFiles/minisat_simp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : minisat/CMakeFiles/minisat_simp.dir/depend

