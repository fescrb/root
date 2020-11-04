list(APPEND root_core_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/array_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/array_slice_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/buffer_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/buffer_slice_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/string_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/string_slice_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/string_view_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/error_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/primitives_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/tuple_tests.cpp)

add_library(root_core_test OBJECT ${root_core_test_sources})