# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cheg/Repos/Master/SpikeLibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cheg/Repos/Master/SpikeLibrary/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_spike.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_spike.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_spike.dir/flags.make

test/CMakeFiles/test_spike.dir/test_main.cpp.o: test/CMakeFiles/test_spike.dir/flags.make
test/CMakeFiles/test_spike.dir/test_main.cpp.o: ../test/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_spike.dir/test_main.cpp.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_spike.dir/test_main.cpp.o -c /home/cheg/Repos/Master/SpikeLibrary/test/test_main.cpp

test/CMakeFiles/test_spike.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_spike.dir/test_main.cpp.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/test/test_main.cpp > CMakeFiles/test_spike.dir/test_main.cpp.i

test/CMakeFiles/test_spike.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_spike.dir/test_main.cpp.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/test/test_main.cpp -o CMakeFiles/test_spike.dir/test_main.cpp.s

test/CMakeFiles/test_spike.dir/test_timeframe.cpp.o: test/CMakeFiles/test_spike.dir/flags.make
test/CMakeFiles/test_spike.dir/test_timeframe.cpp.o: ../test/test_timeframe.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/test_spike.dir/test_timeframe.cpp.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_spike.dir/test_timeframe.cpp.o -c /home/cheg/Repos/Master/SpikeLibrary/test/test_timeframe.cpp

test/CMakeFiles/test_spike.dir/test_timeframe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_spike.dir/test_timeframe.cpp.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/test/test_timeframe.cpp > CMakeFiles/test_spike.dir/test_timeframe.cpp.i

test/CMakeFiles/test_spike.dir/test_timeframe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_spike.dir/test_timeframe.cpp.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/test/test_timeframe.cpp -o CMakeFiles/test_spike.dir/test_timeframe.cpp.s

# Object files for target test_spike
test_spike_OBJECTS = \
"CMakeFiles/test_spike.dir/test_main.cpp.o" \
"CMakeFiles/test_spike.dir/test_timeframe.cpp.o"

# External object files for target test_spike
test_spike_EXTERNAL_OBJECTS =

test/test_spike: test/CMakeFiles/test_spike.dir/test_main.cpp.o
test/test_spike: test/CMakeFiles/test_spike.dir/test_timeframe.cpp.o
test/test_spike: test/CMakeFiles/test_spike.dir/build.make
test/test_spike: src/libspike.so
test/test_spike: /usr/lib/libgsl.so
test/test_spike: /usr/lib/libgslcblas.so
test/test_spike: /usr/lib/libfftw3.so
test/test_spike: /usr/lib/libfftw3f.so
test/test_spike: /usr/lib/libfftw3l.so
test/test_spike: /usr/lib/libfftw3_threads.so
test/test_spike: /usr/lib/libfftw3f_threads.so
test/test_spike: /usr/lib/libfftw3l_threads.so
test/test_spike: /usr/lib/libfftw3_omp.so
test/test_spike: /usr/lib/libfftw3f_omp.so
test/test_spike: /usr/lib/libfftw3l_omp.so
test/test_spike: /usr/lib/libgomp.so
test/test_spike: /usr/lib/libpthread.so
test/test_spike: test/CMakeFiles/test_spike.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_spike"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_spike.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_spike.dir/build: test/test_spike

.PHONY : test/CMakeFiles/test_spike.dir/build

test/CMakeFiles/test_spike.dir/clean:
	cd /home/cheg/Repos/Master/SpikeLibrary/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test_spike.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_spike.dir/clean

test/CMakeFiles/test_spike.dir/depend:
	cd /home/cheg/Repos/Master/SpikeLibrary/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cheg/Repos/Master/SpikeLibrary /home/cheg/Repos/Master/SpikeLibrary/test /home/cheg/Repos/Master/SpikeLibrary/build /home/cheg/Repos/Master/SpikeLibrary/build/test /home/cheg/Repos/Master/SpikeLibrary/build/test/CMakeFiles/test_spike.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_spike.dir/depend

