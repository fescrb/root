# Create a variable with all submodules in order of compilation.
set(submodules 	Base
				Memory
				Containers
				IO
				Math
				 )

# For each submodule we add it to the list of include folders, we 
# add its CMakeLists.txt and finally we add its library to the list 
# of libraries to add to the Core module.
foreach(submodule ${submodules})
	include_directories(${submodule})
	add_subdirectory(${submodule})
	foreach(source ${submodule_sources})
		set(all_submodule_sources ${all_submodule_sources} ${submodule}/${source})
	endforeach(source)
endforeach(submodule)

# We create the library with that dummy file and add the rest of the libraries.
add_library(RootCore ${all_submodule_sources})

set(submodules ${submodules} PARENT_SCOPE)

set(RootCore_LIBRARY RootCore PARENT_SCOPE)

