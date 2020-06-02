add_executable(spike_suscept_mpi suscept_mpi.c)

# add git head and branch (taken from https://github.com/michael-hartmann/caps)
if (EXISTS "${PROJECT_SOURCE_DIR}/.git" AND ${GIT_FOUND})
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_BRANCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    target_compile_definitions(spike_suscept_mpi PRIVATE -DGIT_HEAD="${GIT_COMMIT_HASH}" -DGIT_BRANCH="${GIT_BRANCH}")
    message("Git info added ${GIT_COMMIT_HASH} ${GIT_BRANCH}")
endif ()
target_link_libraries(spike_suscept_mpi
        spike
        MPI::MPI_C
        )
