cmake_minimum_required(VERSION 3.13)
project(SpikeLibrary C CXX)

# set standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# set compile flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

# cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/findFFTW")

# header directory
include_directories("src/")

# add gsl, openmp, fftw
find_package(GSL REQUIRED)
find_package(OpenMP REQUIRED)
find_package(FFTW REQUIRED)

# add catch to project
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/catch/)
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${CATCH_INCLUDE_DIR})
include_directories(CATCH_INCLUDE_DIR)

# add subdirectories
add_subdirectory("app")
add_subdirectory("src")
add_subdirectory("test")
