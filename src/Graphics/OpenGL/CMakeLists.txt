# Add the source files in a separate file.
include(CMakeSources.cmake)

# Inform parent of sources.
set(subfolder_sources ${sources} ${platform_dependent_sources} PARENT_SCOPE)
