list(APPEND root_main_sources ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(android_native_glue ${ANDROID_NDK}/sources/android/native_app_glue/)
    add_library(android_native_glue STATIC ${android_native_glue}/android_native_app_glue.c)
    include_directories(${android_native_glue})
    list(APPEND root_main_sources ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/looper.cpp)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

add_library(root_main STATIC ${root_main_sources})

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    target_link_libraries(android_native_glue root_main)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

install(TARGETS root_main ARCHIVE DESTINATION lib)