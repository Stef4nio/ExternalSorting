# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /cygdrive/c/Users/stef4/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/stef4/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ExternalSorting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ExternalSorting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ExternalSorting.dir/flags.make

CMakeFiles/ExternalSorting.dir/main.cpp.o: CMakeFiles/ExternalSorting.dir/flags.make
CMakeFiles/ExternalSorting.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ExternalSorting.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ExternalSorting.dir/main.cpp.o -c "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/main.cpp"

CMakeFiles/ExternalSorting.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExternalSorting.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/main.cpp" > CMakeFiles/ExternalSorting.dir/main.cpp.i

CMakeFiles/ExternalSorting.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExternalSorting.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/main.cpp" -o CMakeFiles/ExternalSorting.dir/main.cpp.s

# Object files for target ExternalSorting
ExternalSorting_OBJECTS = \
"CMakeFiles/ExternalSorting.dir/main.cpp.o"

# External object files for target ExternalSorting
ExternalSorting_EXTERNAL_OBJECTS =

ExternalSorting.exe: CMakeFiles/ExternalSorting.dir/main.cpp.o
ExternalSorting.exe: CMakeFiles/ExternalSorting.dir/build.make
ExternalSorting.exe: CMakeFiles/ExternalSorting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ExternalSorting.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ExternalSorting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ExternalSorting.dir/build: ExternalSorting.exe

.PHONY : CMakeFiles/ExternalSorting.dir/build

CMakeFiles/ExternalSorting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExternalSorting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExternalSorting.dir/clean

CMakeFiles/ExternalSorting.dir/depend:
	cd "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting" "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting" "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug" "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug" "/cygdrive/e/STEF/WORKSPACE(For C++)/ExternalSorting/cmake-build-debug/CMakeFiles/ExternalSorting.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ExternalSorting.dir/depend

