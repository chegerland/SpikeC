# build the spike library
set(spike_sources
        analytics.c
        utils/ini.c
        utils/log.c
        utils/io_utils.c
        timeframe.c
        neurons.c
        simulations/suscept_sim.c
        signals.c
        spiketrain.c
        statistics.c
        )
add_library(spike SHARED ${spike_sources})

set_target_properties(spike PROPERTIES
VERSION ${PROJECT_VERSION}
SOVERSION 1
)

# link with library
target_link_libraries(spike
        ${GSL_LIBRARY}
        ${GSL_CBLAS_LIBRARY}
        ${FFTW_LIBRARIES}
        m
        OpenMP::OpenMP_C
        )
