# Building in windows
## Required installs & SDKs:
* Visual Studio 2019
* Windows SDK 
* Vulkan SDK

## Environment variables
* `VULKAN_SDK`: Should be automatically set up by the Vulkan SDK installer
* `PATH`: Must include `cl.exe` from the visual studio installation & `rc.exe` from the Windows SDK installation.

## Cmake commands
* `cmake -G "NMake Makefiles" -DCMAKE_INSTALL_PREFIX=<ROOT_FOLDER> -DCMAKE_BUILD_TYPE=Debug`
* `nmake`
* `nmake install`