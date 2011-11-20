# Add the source files in a separate file.
include(CMakeSources.cmake)

# Create a variable with all submodules in order of compilation.
set(subforders 	GLX # This will later be optional.
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

# Inform parent of sources.
set(subfolder_sources ${sources} ${all_subforder_sources} PARENT_SCOPE)
