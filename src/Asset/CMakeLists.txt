include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(CMakeSources.cmake)

# We create the library and add the rest of the libraries.
add_library(RootAsset ${all_subforder_sources} ${sources})

set(RootAsset_LIBRARY RootAsset PARENT_SCOPE)

