cmake_minimum_required(VERSION 3.10)

project(root CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

# Platform defines
if(UNIX)
    add_definitions(-DROOT_LINUX)
endif(UNIX)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DROOT_ASSERT -DROOT_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DROOT_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/memory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/graphics)

add_library(root STATIC $<TARGET_OBJECTS:root_core> 
                        $<TARGET_OBJECTS:root_memory> 
                        $<TARGET_OBJECTS:root_io> 
                        $<TARGET_OBJECTS:root_graphics>)

target_link_libraries(root vulkan glfw3 dl)

install(TARGETS root)

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_executable(root_test $<TARGET_OBJECTS:root_core_test> 
                             $<TARGET_OBJECTS:root_memory_test> 
                             $<TARGET_OBJECTS:root_io_test> 
                             $<TARGET_OBJECTS:root_math_test>)

    target_link_libraries(root_test root gtest_maind gtestd gmockd pthread)

    install(TARGETS root_test)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")