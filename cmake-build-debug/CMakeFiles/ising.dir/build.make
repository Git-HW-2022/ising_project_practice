# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CLionProjects\ising_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CLionProjects\ising_project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ising.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ising.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ising.dir/flags.make

CMakeFiles/ising.dir/main.cpp.obj: CMakeFiles/ising.dir/flags.make
CMakeFiles/ising.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CLionProjects\ising_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ising.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ising.dir\main.cpp.obj -c C:\CLionProjects\ising_project\main.cpp

CMakeFiles/ising.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ising.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CLionProjects\ising_project\main.cpp > CMakeFiles\ising.dir\main.cpp.i

CMakeFiles/ising.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ising.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CLionProjects\ising_project\main.cpp -o CMakeFiles\ising.dir\main.cpp.s

# Object files for target ising
ising_OBJECTS = \
"CMakeFiles/ising.dir/main.cpp.obj"

# External object files for target ising
ising_EXTERNAL_OBJECTS =

ising.exe: CMakeFiles/ising.dir/main.cpp.obj
ising.exe: CMakeFiles/ising.dir/build.make
ising.exe: CMakeFiles/ising.dir/linklibs.rsp
ising.exe: CMakeFiles/ising.dir/objects1.rsp
ising.exe: CMakeFiles/ising.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CLionProjects\ising_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ising.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ising.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ising.dir/build: ising.exe

.PHONY : CMakeFiles/ising.dir/build

CMakeFiles/ising.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ising.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ising.dir/clean

CMakeFiles/ising.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CLionProjects\ising_project C:\CLionProjects\ising_project C:\CLionProjects\ising_project\cmake-build-debug C:\CLionProjects\ising_project\cmake-build-debug C:\CLionProjects\ising_project\cmake-build-debug\CMakeFiles\ising.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ising.dir/depend

