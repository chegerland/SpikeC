add_executable(suscept_test suscept_test.c)
target_link_libraries(suscept_test
        spike
        OpenMP::OpenMP_C
        )

add_executable(test test.c)
target_link_libraries(test
        spike
        )

add_executable(suscept_mpi suscept_mpi.c)
target_link_libraries(suscept_mpi
        spike
        MPI::MPI_C
        )
