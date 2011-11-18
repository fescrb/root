include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create a variable with all submodules in order of compilation.
set(subforders 	OpenGL # This will later be optional.
				 )

# For each submodule we add it to the list of include folders, we 
# add its CMakeLists.txt and finally we add its library to the list 
# of libraries to add to the Core module.
foreach(subforder ${subforders})
	include_directories(${subforder})
	add_subdirectory(${subforder})
	foreach(source ${subfolder_sources})
		set(all_subforder_sources ${all_subforder_sources} ${subforder}/${source})
	endforeach(source)
endforeach(subforder)

# We create the library with that dummy file and add the rest of the libraries.
add_library(RootGraphics ${all_subforder_sources})

set(RootGraphics_LIBRARY RootGraphics PARENT_SCOPE)

