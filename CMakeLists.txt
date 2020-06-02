cmake_minimum_required(VERSION 3.13)
project(SpikeLibrary LANGUAGES C VERSION 0.1 DESCRIPTION "Tools for CHEs master thesis")

# set standard
set(CMAKE_C_STANDARD 11)

# set compile flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Werror -Wpedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/findFFTW")

# add gsl, mpi, fftw
find_package(Git)
find_package(GSL REQUIRED)
find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)
find_package(FFTW REQUIRED)

# add subdirectories
add_subdirectory("app")
add_subdirectory("src")

# install targets
include(GNUInstallDirs)
install(TARGETS spike
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN *.h
        )

# testing
include(CTest)
enable_testing()
add_subdirectory("test")
