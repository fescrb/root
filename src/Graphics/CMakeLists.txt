include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create a variable with all submodules in order of compilation.
set(subforders 	OpenGL # This will later be optional.
				 )

# For each subfolder we add it to the list of include folders, we 
# add its CMakeLists.txt and finally we add its sources to the list 
# of sources to add to the Graphics module.
foreach(subforder ${subforders})
	include_directories(${subforder})
	add_subdirectory(${subforder})
	foreach(source ${subfolder_sources})
		set(all_subforder_sources ${all_subforder_sources} ${subforder}/${source})
	endforeach(source)
endforeach(subforder)

# We create the library and add the rest of the libraries.
add_library(RootGraphics ${all_subforder_sources})

target_link_libraries(RootGraphics ${Graphics_LIBRARIES})

set(RootGraphics_LIBRARY RootGraphics PARENT_SCOPE)

