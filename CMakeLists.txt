cmake_minimum_required(VERSION 3.10)

project(root CXX)

find_package(Vulkan REQUIRED)

include_directories(SYSTEM ${Vulkan_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/build/RootSetup.cmake)

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_definitions(-DROOT_TESTS_BINARY_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/bin\")
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/memory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/graphics)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/root/asset)

add_library(root STATIC $<TARGET_OBJECTS:root_core> 
                        $<TARGET_OBJECTS:root_memory> 
                        $<TARGET_OBJECTS:root_io> 
                        $<TARGET_OBJECTS:root_graphics>
                        $<TARGET_OBJECTS:root_asset>)

target_link_libraries(root ${Vulkan_LIBRARY} glfw3 dl pthread)

install(TARGETS root ARCHIVE DESTINATION lib)

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    add_executable(root_test $<TARGET_OBJECTS:root_core_test> 
                             $<TARGET_OBJECTS:root_memory_test> 
                             $<TARGET_OBJECTS:root_io_test> 
                             $<TARGET_OBJECTS:root_math_test> 
                             $<TARGET_OBJECTS:root_asset_test>)

    target_link_libraries(root_test root gtest_maind gtestd gmockd)

    install(TARGETS root_test RUNTIME DESTINATION bin)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")