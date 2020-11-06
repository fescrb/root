list(APPEND root_graphics_sources ${CMAKE_CURRENT_SOURCE_DIR}/device.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/instance.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/physical_device.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/surface.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/vk_format.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/swapchain.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp)

add_library(root_graphics OBJECT ${root_graphics_sources})

#if(${CMAKE_BUILD_TYPE} MATCHES "Test")
#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
#endif(${CMAKE_BUILD_TYPE} MATCHES "Test")