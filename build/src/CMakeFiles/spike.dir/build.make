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
include src/CMakeFiles/spike.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/spike.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/spike.dir/flags.make

src/CMakeFiles/spike.dir/log.c.o: src/CMakeFiles/spike.dir/flags.make
src/CMakeFiles/spike.dir/log.c.o: ../src/log.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/spike.dir/log.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spike.dir/log.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/src/log.c

src/CMakeFiles/spike.dir/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spike.dir/log.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/src/log.c > CMakeFiles/spike.dir/log.c.i

src/CMakeFiles/spike.dir/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spike.dir/log.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/src/log.c -o CMakeFiles/spike.dir/log.c.s

src/CMakeFiles/spike.dir/neurons.c.o: src/CMakeFiles/spike.dir/flags.make
src/CMakeFiles/spike.dir/neurons.c.o: ../src/neurons.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/spike.dir/neurons.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spike.dir/neurons.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/src/neurons.c

src/CMakeFiles/spike.dir/neurons.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spike.dir/neurons.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/src/neurons.c > CMakeFiles/spike.dir/neurons.c.i

src/CMakeFiles/spike.dir/neurons.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spike.dir/neurons.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/src/neurons.c -o CMakeFiles/spike.dir/neurons.c.s

src/CMakeFiles/spike.dir/signals.c.o: src/CMakeFiles/spike.dir/flags.make
src/CMakeFiles/spike.dir/signals.c.o: ../src/signals.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/spike.dir/signals.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spike.dir/signals.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/src/signals.c

src/CMakeFiles/spike.dir/signals.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spike.dir/signals.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/src/signals.c > CMakeFiles/spike.dir/signals.c.i

src/CMakeFiles/spike.dir/signals.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spike.dir/signals.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/src/signals.c -o CMakeFiles/spike.dir/signals.c.s

src/CMakeFiles/spike.dir/statistics.c.o: src/CMakeFiles/spike.dir/flags.make
src/CMakeFiles/spike.dir/statistics.c.o: ../src/statistics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/spike.dir/statistics.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spike.dir/statistics.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/src/statistics.c

src/CMakeFiles/spike.dir/statistics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spike.dir/statistics.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/src/statistics.c > CMakeFiles/spike.dir/statistics.c.i

src/CMakeFiles/spike.dir/statistics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spike.dir/statistics.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/src/statistics.c -o CMakeFiles/spike.dir/statistics.c.s

src/CMakeFiles/spike.dir/timeframe.c.o: src/CMakeFiles/spike.dir/flags.make
src/CMakeFiles/spike.dir/timeframe.c.o: ../src/timeframe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/spike.dir/timeframe.c.o"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spike.dir/timeframe.c.o   -c /home/cheg/Repos/Master/SpikeLibrary/src/timeframe.c

src/CMakeFiles/spike.dir/timeframe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spike.dir/timeframe.c.i"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheg/Repos/Master/SpikeLibrary/src/timeframe.c > CMakeFiles/spike.dir/timeframe.c.i

src/CMakeFiles/spike.dir/timeframe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spike.dir/timeframe.c.s"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheg/Repos/Master/SpikeLibrary/src/timeframe.c -o CMakeFiles/spike.dir/timeframe.c.s

# Object files for target spike
spike_OBJECTS = \
"CMakeFiles/spike.dir/log.c.o" \
"CMakeFiles/spike.dir/neurons.c.o" \
"CMakeFiles/spike.dir/signals.c.o" \
"CMakeFiles/spike.dir/statistics.c.o" \
"CMakeFiles/spike.dir/timeframe.c.o"

# External object files for target spike
spike_EXTERNAL_OBJECTS =

src/libspike.so: src/CMakeFiles/spike.dir/log.c.o
src/libspike.so: src/CMakeFiles/spike.dir/neurons.c.o
src/libspike.so: src/CMakeFiles/spike.dir/signals.c.o
src/libspike.so: src/CMakeFiles/spike.dir/statistics.c.o
src/libspike.so: src/CMakeFiles/spike.dir/timeframe.c.o
src/libspike.so: src/CMakeFiles/spike.dir/build.make
src/libspike.so: /usr/lib/libgsl.so
src/libspike.so: /usr/lib/libgslcblas.so
src/libspike.so: /usr/lib/libfftw3.so
src/libspike.so: /usr/lib/libfftw3f.so
src/libspike.so: /usr/lib/libfftw3l.so
src/libspike.so: /usr/lib/libfftw3_threads.so
src/libspike.so: /usr/lib/libfftw3f_threads.so
src/libspike.so: /usr/lib/libfftw3l_threads.so
src/libspike.so: /usr/lib/libfftw3_omp.so
src/libspike.so: /usr/lib/libfftw3f_omp.so
src/libspike.so: /usr/lib/libfftw3l_omp.so
src/libspike.so: /usr/lib/libgomp.so
src/libspike.so: /usr/lib/libpthread.so
src/libspike.so: src/CMakeFiles/spike.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cheg/Repos/Master/SpikeLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C shared library libspike.so"
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spike.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/spike.dir/build: src/libspike.so

.PHONY : src/CMakeFiles/spike.dir/build

src/CMakeFiles/spike.dir/clean:
	cd /home/cheg/Repos/Master/SpikeLibrary/build/src && $(CMAKE_COMMAND) -P CMakeFiles/spike.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/spike.dir/clean

src/CMakeFiles/spike.dir/depend:
	cd /home/cheg/Repos/Master/SpikeLibrary/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cheg/Repos/Master/SpikeLibrary /home/cheg/Repos/Master/SpikeLibrary/src /home/cheg/Repos/Master/SpikeLibrary/build /home/cheg/Repos/Master/SpikeLibrary/build/src /home/cheg/Repos/Master/SpikeLibrary/build/src/CMakeFiles/spike.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/spike.dir/depend

