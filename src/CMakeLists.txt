set(modules Core
			Graphics
			Asset )

foreach(module ${modules})
	set(submodules )
	add_subdirectory(${module})
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${module})
	foreach(submodule ${submodules})
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${module}/${submodule})
		message("Adding include directory " ${module}/${submodule} ".")
	endforeach(submodule)
endforeach(module)

set(Root_LIBRARIES ${RootCore_LIBRARY} ${RootGraphics_LIBRARY} ${RootAsset_LIBRARY})

if(${_ROOT_COMPILE_UNIT_TESTS})
	message("Adding unit tests....")
	add_subdirectory("Unit Testing")
endif(${_ROOT_COMPILE_UNIT_TESTS})

if(${ROOT_COMPILE_DEMOS})
	add_subdirectory("Demos")
endif(${ROOT_COMPILE_DEMOS})
