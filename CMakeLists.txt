project(Root)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS})

# Look for OGL, mandatory for now.
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
set(Graphics_LIBRARIES ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
message("Using OpenGL as graphics library.")

if(${CMAKE_BUILD_TYPE} MATCHES "Testing")
	message("Option: Unit Tests.")

	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	set(CMAKE_BUILD_TYPE "Debug")
	set(_ROOT_COMPILE_UNIT_TESTS 1)
endif(${CMAKE_BUILD_TYPE} MATCHES "Testing")

if(${ROOT_USE_SIMD})
	message("Option: SIMD instructions.")
	
	add_definitions(-D_ROOT_USE_SIMD)
	
	# If target architecture is not specified.
	if(NOT ${ROOT_PROCESSOR_TARGET})
		set(ROOT_PROCESSOR_TARGET ${CMAKE_SYSTEM_PROCESSOR})
	endif(NOT ${ROOT_PROCESSOR_TARGET})
	
	if(${CMAKE_SYSTEM_PROCESSOR} MATCHES ^x86.*)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
	endif(${CMAKE_SYSTEM_PROCESSOR} MATCHES ^x86.*)
	
endif(${ROOT_USE_SIMD})

if(${ROOT_COMPILE_DEMOS})
	message("Option: Compile demonstration programs.")
endif(${ROOT_COMPILE_DEMOS})

add_subdirectory(src)
