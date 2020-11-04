list(APPEND root_io_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/formatter_tests.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/buffer_stream_tests.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/writer_tests.cpp)

add_library(root_io_test OBJECT ${root_io_test_sources})