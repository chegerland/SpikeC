add_executable(spike_suscept_mpi suscept_mpi.c)
target_link_libraries(spike_suscept_mpi
        spike
        MPI::MPI_C
        )
