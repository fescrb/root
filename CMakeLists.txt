project(Root)

cmake_minimum_required(VERSION 2.6)

if(${CMAKE_BUILD_TYPE} MATCHES "Testing")
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	message(${Boost_LIBRARIES})
	set(CMAKE_BUILD_TYPE "Debug")
	set(COMPILE_UNIT_TESTS 1)
endif(${CMAKE_BUILD_TYPE} MATCHES "Testing")

add_subdirectory(src)
