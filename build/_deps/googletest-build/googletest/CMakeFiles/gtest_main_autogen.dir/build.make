# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build

# Utility rule file for gtest_main_autogen.

# Include any custom commands dependencies for this target.
include _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/progress.make

_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target gtest_main"
	cd /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-build/googletest && /usr/bin/cmake -E cmake_autogen /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/AutogenInfo.json ""

gtest_main_autogen: _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen
gtest_main_autogen: _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/build.make
.PHONY : gtest_main_autogen

# Rule to build all files generated by this target.
_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/build: gtest_main_autogen
.PHONY : _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/build

_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/clean:
	cd /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-build/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main_autogen.dir/cmake_clean.cmake
.PHONY : _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/clean

_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/depend:
	cd /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2 /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-src/googletest /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-build/googletest /home/ferbuono/fiuba/taller/TP_Jazz_Jackrabbit_2/build/_deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/googletest-build/googletest/CMakeFiles/gtest_main_autogen.dir/depend

