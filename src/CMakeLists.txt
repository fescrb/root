set(modules Core)

foreach(module ${modules})
	add_subdirectory(${module})
	foreach(submodule ${submodules})
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${module}/${submodule})
		message("Adding include directory " ${module}/${submodule} ".")
	endforeach(submodule)
endforeach(module)

if(${_ROOT_COMPILE_UNIT_TESTS})
	message("Adding unit tests....")
	add_subdirectory("Unit Testing")
endif(${_ROOT_COMPILE_UNIT_TESTS})
