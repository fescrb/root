# Add the source files in a separate file.
include(CMakeSources.cmake)

# Include platform-dependent subfolder.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_subdirectory(Unix)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_subdirectory(Linux)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Inform parent of sources.
set(submodule_sources ${sources} ${platform_dependent_sources} PARENT_SCOPE)
