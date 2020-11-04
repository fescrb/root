list(APPEND root_io_sources ${CMAKE_CURRENT_SOURCE_DIR}/format.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/buffer_stream.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/file_stream.cpp)

add_library(root_io OBJECT ${root_io_sources})

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")