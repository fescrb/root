list(APPEND root_graphics_sources ${CMAKE_CURRENT_SOURCE_DIR}/device.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/instance.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/physical_device.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/surface.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/vk_format.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/swapchain.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline_layout.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/renderpass.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/command_pool.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/command_buffer.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/shader_module.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/vk_allocation_callbacks.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/semaphore.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp)

add_library(root_graphics OBJECT ${root_graphics_sources})

#if(${CMAKE_BUILD_TYPE} MATCHES "Test")
#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
#endif(${CMAKE_BUILD_TYPE} MATCHES "Test")