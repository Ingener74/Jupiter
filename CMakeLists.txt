cmake_minimum_required(VERSION 2.8)

# find png
find_package(PNG REQUIRED)
if(PNG_FOUND)
    add_definitions(-DPNG_FOUND)
endif(PNG_FOUND)

# include dependencies
include_directories(
    ${PNG_INCLUDE_DIRS}
    ${ANDROID_NDK}/platforms/${ANDROID_NATIVE_API_LEVEL}/arch-arm/usr/include
    ${ANDROID_NDK}/sources/android/native_app_glue
)

add_definitions(
    -std=c++11# -pedantic
    ${PNG_DEFINITIONS}
)

add_subdirectory(AndroidNDKGame)
