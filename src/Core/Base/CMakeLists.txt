# Add the source files in a separate file.
include(CMakeSources.cmake)

# Inform parent of sources.
set(submodule_sources ${sources} PARENT_SCOPE)
