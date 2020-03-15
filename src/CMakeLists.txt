# build the spike library
file(GLOB_RECURSE spike_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.c")
add_library(spike SHARED ${spike_sources})

# link with library
target_link_libraries(spike
        ${GSL_LIBRARY}
        ${GSL_CBLAS_LIBRARY}
        ${FFTW_LIBRARIES}
        m
        OpenMP::OpenMP_C
        )
