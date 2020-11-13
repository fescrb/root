list(APPEND root_memory_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/allocator_tests.cpp
                                     ${CMAKE_CURRENT_SOURCE_DIR}/managed_ptr_tests.cpp
                                     ${CMAKE_CURRENT_SOURCE_DIR}/reference_counter_tests.cpp
                                     ${CMAKE_CURRENT_SOURCE_DIR}/weak_ptr_tests.cpp
                                     ${CMAKE_CURRENT_SOURCE_DIR}/strong_ptr_tests.cpp)

add_library(root_memory_test OBJECT ${root_memory_test_sources})