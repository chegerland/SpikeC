# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cheg/Repos/Master/SpikeLibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cheg/Repos/Master/SpikeLibrary/build

# Include any dependencies generated for this target.
include app/CMakeFiles/suscept_test.dir/depend.make

# Include the progress variables for this target.
include app/CMakeFiles/suscept_test.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/suscept_test.dir/flags.make

app/CMakeFiles/suscept_test.dir/suscept_test.c.o: app/CMakeFiles/suscept_test.dir/flags.make
app/CMakeFiles/suscept_test.dir/suscept_test.c.o: ../app/suscept_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object app/CMakeFiles/suscept_test.dir/suscept_test.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/suscept_test.dir/suscept_test.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/app/suscept_test.c

app/CMakeFiles/suscept_test.dir/suscept_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/suscept_test.dir/suscept_test.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/app/suscept_test.c > CMakeFiles/suscept_test.dir/suscept_test.c.i

app/CMakeFiles/suscept_test.dir/suscept_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/suscept_test.dir/suscept_test.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/app/suscept_test.c -o CMakeFiles/suscept_test.dir/suscept_test.c.s

# Object files for target suscept_test
suscept_test_OBJECTS = \
"CMakeFiles/suscept_test.dir/suscept_test.c.o"

# External object files for target suscept_test
suscept_test_EXTERNAL_OBJECTS =

app/suscept_test: app/CMakeFiles/suscept_test.dir/suscept_test.c.o
app/suscept_test: app/CMakeFiles/suscept_test.dir/build.make
app/suscept_test: src/libspike.so
app/suscept_test: /usr/lib/libgomp.so
app/suscept_test: /usr/lib/libpthread.so
app/suscept_test: /usr/lib/libgsl.so
app/suscept_test: /usr/lib/libgslcblas.so
app/suscept_test: /usr/lib/libfftw3.so
app/suscept_test: /usr/lib/libfftw3f.so
app/suscept_test: /usr/lib/libfftw3l.so
app/suscept_test: /usr/lib/libfftw3_threads.so
app/suscept_test: /usr/lib/libfftw3f_threads.so
app/suscept_test: /usr/lib/libfftw3l_threads.so
app/suscept_test: /usr/lib/libfftw3_omp.so
app/suscept_test: /usr/lib/libfftw3f_omp.so
app/suscept_test: /usr/lib/libfftw3l_omp.so
app/suscept_test: app/CMakeFiles/suscept_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable suscept_test"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/suscept_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/suscept_test.dir/build: app/suscept_test

.PHONY : app/CMakeFiles/suscept_test.dir/build

app/CMakeFiles/suscept_test.dir/clean:
	cd /home/cheg/Repos/Master/SpikeLibrary/build/app && $(CMAKE_COMMAND) -P CMakeFiles/suscept_test.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/suscept_test.dir/clean

app/CMakeFiles/suscept_test.dir/depend:
	cd /home/cheg/Repos/Master/SpikeLibrary/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cheg/Repos/Master/SpikeLibrary /home/cheg/Repos/Master/SpikeLibrary/app /home/cheg/Repos/Master/SpikeLibrary/build /home/cheg/Repos/Master/SpikeLibrary/build/app /home/cheg/Repos/Master/SpikeLibrary/build/app/CMakeFiles/suscept_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/suscept_test.dir/depend

