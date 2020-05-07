# add sources to test
add_executable(test_timeframe test_timeframe.c)
target_link_libraries(test_timeframe
        spike
        )
