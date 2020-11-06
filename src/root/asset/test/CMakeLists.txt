list(APPEND root_asset_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/asset_manager_tests.cpp)

add_library(root_asset_test OBJECT ${root_asset_test_sources})