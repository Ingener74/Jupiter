cmake_minimum_required(VERSION 2.8.11)

set(EXT_BOX2D ext_Box2D)

if(MINGW)
    ExternalProject_Add(
        ${EXT_BOX2D}
        GIT_REPOSITORY      https://github.com/erincatto/Box2D.git
        GIT_TAG             v2.3.1
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/box2d.patch
        CONFIGURE_COMMAND   cmake ${CMAKE_BINARY_DIR}/3rdparty/Box2D/${EXT_BOX2D}-prefix/src/${EXT_BOX2D}/Box2D 
                                    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}                            
                                    -DBOX2D_INSTALL=ON
                                    -DBOX2D_BUILD_EXAMPLES=OFF
                                    #-DBOX2D_BUILD_SHARED=ON
                                    #-DBOX2D_BUILD_STATIC=ON
                                    -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
