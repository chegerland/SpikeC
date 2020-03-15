# add sources to test
file(GLOB_RECURSE test_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_executable(test_spike ${test_sources})


# link with library
target_link_libraries(test_spike PRIVATE
        catch
        spike
        )
