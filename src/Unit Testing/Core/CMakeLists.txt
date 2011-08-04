set(submodules 	Base
				Math)

foreach(submodule ${submodules})
	add_subdirectory(${submodule})
	foreach(source_file ${test_sources})
		set(all_test_sources ${all_test_sources} ${submodule}/${source_file})
	endforeach(source_file)
endforeach(submodule)

add_executable(core_test Core.cpp ${all_test_sources})
target_link_libraries(core_test ${Boost_LIBRARIES} ${RootCore_LIBRARY})
