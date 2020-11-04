set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

# Platform defines
if(UNIX)
    add_definitions(-DROOT_LINUX)
endif(UNIX) 

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DROOT_ASSERT -DROOT_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

if(${CMAKE_BUILD_TYPE} MATCHES "Test")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DROOT_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES "Test")