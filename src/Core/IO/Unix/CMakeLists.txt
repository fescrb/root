# Add the platform-dependent source files in a separate file.
include(CMakeSources.cmake)

# We add the name of the folder to each source to get the complete names.
foreach(source ${sources})
	set(complete_source_names ${complete_source_names} Unix/${source})
endforeach(source)

# Send the sources to the parent CMakeLists.txt.
set(platform_dependent_sources ${platform_dependent_sources} ${complete_source_names} PARENT_SCOPE)


