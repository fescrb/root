# Platform defines
list(APPEND root_link_libraries ${Vulkan_LIBRARY})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DROOT_LINUX)
    list(APPEND root_link_libraries glfw3 dl pthread)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(CMAKE_ANDROID_API 26)
    add_definitions(-DROOT_ANDROID)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

if(WIN32)
    add_definitions(/DROOT_WIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")
endif(WIN32) 

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    if(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Z7")
        add_definitions(-DROOT_ASSERT -DROOT_DEBUG)
    else(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
        add_definitions(-DROOT_ASSERT -DROOT_DEBUG)
    endif(WIN32) 
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DROOT_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")