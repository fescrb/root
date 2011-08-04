# Add the source files in a separate file.
include(CMakeSources.cmake)

# Include platform-dependent subfolder.
#add_subdirectory(${CMAKE_SYSTEM_NAME})

# Inform parent of sources.
set(submodule_sources ${sources} ${platform_dependent_sources} PARENT_SCOPE)
