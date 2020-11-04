list(APPEND root_math_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/mat4x4.tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/math_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/vec3_tests.cpp
                                   ${CMAKE_CURRENT_SOURCE_DIR}/vec4_tests.cpp)

add_library(root_math_test OBJECT ${root_math_test_sources})