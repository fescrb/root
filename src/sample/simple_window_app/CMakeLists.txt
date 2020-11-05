cmake_minimum_required(VERSION 3.10)

project(simple_window_app CXX)

set(ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${ROOT_FOLDER}/include)

link_directories(${ROOT_FOLDER}/lib)

include(${ROOT_FOLDER}/src/build/RootSetup.cmake)

list(APPEND simple_window_app_sources ${CMAKE_CURRENT_SOURCE_DIR}/simple_window_app.cpp)

add_executable(simple_window_app ${simple_window_app_sources})

target_link_libraries(simple_window_app root vulkan glfw3 dl pthread)

install(TARGETS simple_window_app RUNTIME DESTINATION bin)