cmake_minimum_required(VERSION 2.8.11)

set(EXT_GMOCK ext_gmock)

if(MINGW OR MSYS)
elseif(EMSCRIPTEN)
elseif(ANDROID)
elseif(APPLE)
    ExternalProject_Add(
        ${EXT_GMOCK}
        URL                 https://googlemock.googlecode.com/files/gmock-1.7.0.zip
        CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        INSTALL_COMMAND     mkdir -p ${3RDPARTY_INSTALL}/include && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}/include ${3RDPARTY_INSTALL} &&
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}/gtest/include ${3RDPARTY_INSTALL} &&
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock_main.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/gtest/libgtest.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/gtest/libgtest_main.a ${3RDPARTY_INSTALL}/lib
    )
else()
    ExternalProject_Add(
        ${EXT_GMOCK}
        URL                 https://googlemock.googlecode.com/files/gmock-1.7.0.zip
        CMAKE_ARGS          -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        INSTALL_COMMAND     mkdir -p ${3RDPARTY_INSTALL}/include && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}/include ${3RDPARTY_INSTALL} &&
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}/gtest/include ${3RDPARTY_INSTALL} &&
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/libgmock_main.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/gtest/libgtest.a ${3RDPARTY_INSTALL}/lib && 
                            cp -R ${CMAKE_BINARY_DIR}/3rdparty/gmock/${EXT_GMOCK}-prefix/src/${EXT_GMOCK}-build/gtest/libgtest_main.a ${3RDPARTY_INSTALL}/lib
    )
endif()

