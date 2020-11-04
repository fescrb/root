if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")