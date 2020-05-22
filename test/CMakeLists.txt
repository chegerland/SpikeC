# add sources to test
add_executable(test_spike
        test_main.c
        )
target_link_libraries(test_spike
        spike
        )

