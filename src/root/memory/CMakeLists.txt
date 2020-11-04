list(APPEND root_memory_sources ${CMAKE_CURRENT_SOURCE_DIR}/allocator.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/system_allocator.cpp)

add_library(root_memory OBJECT ${root_memory_sources})

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")