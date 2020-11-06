list(APPEND root_asset_sources ${CMAKE_CURRENT_SOURCE_DIR}/asset_manager.cpp)

add_library(root_asset OBJECT ${root_asset_sources})

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")