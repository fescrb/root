set(modules Core)

foreach(module ${modules})
	add_subdirectory(${module})
endforeach(module)
