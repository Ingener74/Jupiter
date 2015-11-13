cmake_minimum_required(VERSION 3.0)

set(EXT_POCO ext_POCO)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_POCO}
        URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DENABLE_DATA_ODBC=OFF
                            -DENABLE_DATA_MYSQL=ON
                            -DENABLE_APACHECONNECTOR=OFF
                            -DENABLE_POCODOC=OFF
                            -DENABLE_PDF=OFF
                            -DENABLE_PAGECOMPILER=OFF
                            -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                            -DENABLE_ZIP=OFF
                            -DENABLE_XML=OFF
                            -DENABLE_MONGODB=ON
                            -DENABLE_TESTS=OFF
                            -DPOCO_STATIC=OFF
                            -DFORCE_OPENSSL=OFF
                            # -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                            # -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                            # -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
    )
# elseif(MSVC)
#     ExternalProject_Add(
#         ${EXT_POCO}
#         URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
#         CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
#                             -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#                             -DENABLE_DATA_ODBC=OFF
#                             -DENABLE_APACHECONNECTOR=OFF
#                             -DENABLE_POCODOC=OFF
#                             -DENABLE_PDF=OFF
#                             -DENABLE_PAGECOMPILER=OFF
#                             -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
#                             -DENABLE_TESTS=OFF
#                             -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
#     )

elseif(APPLE)
    ExternalProject_Add(
        ${EXT_POCO}
        URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DENABLE_DATA_ODBC=OFF
                            -DENABLE_DATA_MYSQL=OFF
                            -DENABLE_APACHECONNECTOR=OFF
                            -DENABLE_POCODOC=OFF
                            -DENABLE_PDF=OFF
                            -DENABLE_PAGECOMPILER=OFF
                            -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                            -DENABLE_ZIP=OFF
                            -DENABLE_XML=OFF
                            -DENABLE_MONGODB=OFF
                            -DENABLE_TESTS=OFF
                            -DPOCO_STATIC=ON
                            -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                            -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                            -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
    )

elseif(EMSCRIPTEN)
    ExternalProject_Add(
        ${EXT_POCO}
        URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DENABLE_DATA_ODBC=OFF
                            -DENABLE_DATA_MYSQL=OFF
                            -DENABLE_APACHECONNECTOR=OFF
                            -DENABLE_POCODOC=OFF
                            -DENABLE_PDF=OFF
                            -DENABLE_PAGECOMPILER=OFF
                            -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                            -DENABLE_ZIP=OFF
                            -DENABLE_XML=OFF
                            -DENABLE_MONGODB=OFF
                            -DENABLE_TESTS=OFF
                            -DPOCO_STATIC=ON
                            -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                            -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                            -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
                            -DANDROID_ABI=${ANDROID_ABI}
                            -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
    )

elseif(ANDROID)
    ExternalProject_Add(
        ${EXT_POCO}
        URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DENABLE_DATA_ODBC=OFF
                            -DENABLE_DATA_MYSQL=OFF
                            -DENABLE_APACHECONNECTOR=OFF
                            -DENABLE_POCODOC=OFF
                            -DENABLE_PDF=OFF
                            -DENABLE_PAGECOMPILER=OFF
                            -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                            -DENABLE_ZIP=OFF
                            -DENABLE_XML=OFF
                            -DENABLE_MONGODB=OFF
                            -DENABLE_TESTS=OFF
                            -DPOCO_STATIC=ON
                            # -DOPENSSL_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                            # -DOPENSSL_CRYPTO_LIBRARY=${3RDPARTY_INSTALL}/lib/libcrypto.a
                            # -DOPENSSL_SSL_LIBRARY=${3RDPARTY_INSTALL}/lib/libssl.a
                            -DANDROID_ABI=${ANDROID_ABI}
                            -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
    )

# elseif(BLACKBERRY)
#     # прокинуть свойства для блэкбери, без этого беда
#     
#     set(CXX_FLAGS "-DPOCO_OS_FAMILY_UNIX -D__EXT_POSIX1_200112 -D__EXT_QNX")
#     
#     ExternalProject_Add(
#         ${EXT_POCO}
#         URL         http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
#         CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
#                     -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
#                     -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#                     -DCMAKE_C_FLAGS=${CXX_FLAGS}
#                     -DCMAKE_CXX_FLAGS=${CXX_FLAGS}
#                     -DENABLE_DATA_ODBC=OFF
#                     -DENABLE_APACHECONNECTOR=OFF
#                     -DENABLE_POCODOC=OFF
#                     -DENABLE_PDF=OFF
#                     -DENABLE_PAGECOMPILER=OFF
#                     -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
#                     -DENABLE_TESTS=OFF
#                     -DPOCO_STATIC=OFF
#     )

else()
    ExternalProject_Add(
        ${EXT_POCO}
        URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DENABLE_DATA_ODBC=OFF
                            -DENABLE_APACHECONNECTOR=OFF
                            -DENABLE_POCODOC=OFF
                            -DENABLE_PDF=OFF
                            -DENABLE_PAGECOMPILER=OFF
                            -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                            -DENABLE_TESTS=OFF
    )
endif()
