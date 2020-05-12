# build the spike library
set(spike_sources
        utils/ini.c
        utils/log.c
        timeframe.c
        neurons/if_neurons.c
        neurons/ifac_neurons.c
        simulations/suscept_sim.c
        signals.c
        statistics.c
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
