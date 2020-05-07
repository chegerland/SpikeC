# build the spike library
set(spike_sources
        ini/ini.c
        log/log.c
        neurons/if_neurons.c
        neurons/ifac_neurons.c
        signals.c
        statistics.c
        timeframe.c
        )
add_library(spike SHARED ${spike_sources})

# link with library
target_link_libraries(spike
        ${GSL_LIBRARY}
        ${GSL_CBLAS_LIBRARY}
        ${FFTW_LIBRARIES}
        m
        OpenMP::OpenMP_C
        )
