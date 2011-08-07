# Set the install prefix
set(CMAKE_INSTALL_PREFIX ${Root_SOURCE_DIR}/demos)

# Create a variable with all demos in order of compilation.
set(demos 		Test
				 )

# Compile each demo.
foreach(demo ${demos})
	add_subdirectory(${demo})
endforeach(demo)
