list(APPEND root_core_sources ${CMAKE_CURRENT_SOURCE_DIR}/assert.cpp)

add_library(root_core OBJECT ${root_core_sources})

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")