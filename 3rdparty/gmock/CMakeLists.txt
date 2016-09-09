cmake_minimum_required(VERSION 2.8.11)

set(EXT_GTEST ext_gmock)

if(MINGW OR MSYS)
elseif(EMSCRIPTEN)
elseif(ANDROID)
elseif(APPLE)
    ExternalProject_Add(
        ${EXT_GTEST}
        URL                 https://github.com/google/googletest/archive/master.zip
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
    )
else()
    ExternalProject_Add(
        ${EXT_GTEST}
        URL                 https://github.com/google/googletest/archive/master.zip
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    )
endif()

set(GTEST_LIBRARIES gmock gtest gmock_main gtest_main CACHE STRING "" FORCE)
message(STATUS "gtest libraries ${GTEST_LIBRARIES}")

