# Add the sources to the compilation.
set(sources test.cpp)

# Add the executable to compile.
add_executable(test ${sources})

# Install in the demo folder root.
install(TARGETS test RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

# Link to the root libraries.
target_link_libraries(test ${Root_LIBRARIES})
