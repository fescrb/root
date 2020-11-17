# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("simple_app")

set (ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../)

include(${ROOT_DIR}/src/build/RootSetup.cmake)

add_subdirectory(${ROOT_DIR} ./root)

include_directories(${ROOT_DIR}/include)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )


target_link_libraries( native-lib
                       android
                       root root_main
                       log )