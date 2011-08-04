#include "ApplicationEnvironment.h"

#include "Path.h"

using namespace root::io;

Path* ApplicationEnvironment::getPresentWorkingDirectory(Allocator* allocator) {
	
}

Path* ApplicationEnvironment::getExecutablePath(Allocator* allocator) {
	
}

Path* ApplicationEnvironment::getHomeDirectory(Allocator* allocator) {
	
}

Path* ApplicationEnvironment::getRootDirectory(Allocator* allocator) {
	return new (allocator) Path("/");
}