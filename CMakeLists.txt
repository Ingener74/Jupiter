cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

if(MINGW OR MSYS)
    message(STATUS "MinGW or MSYS build")
elseif(EMSCRIPTEN)
    message(STATUS "Emscripten build")
elseif(ANDROID)
    message(STATUS "Android build")
elseif(APPLE)
    message(STATUS "MacOS build")
else()
    message(STATUS "Linux build")
endif()

# Под Emscripten и Android надобности в этих библиотеках нет
if(MINGW OR MSYS)
    option(FIND_PACKAGE_FREEGLUT      "force find_package for FreeGLUT"  OFF)
    option(FIND_PACKAGE_GLFW          "force find_package for GLFW"      OFF) 
    option(FIND_PACKAGE_GLEW          "force find_package for GLEW"      OFF)
elseif(EMSCRIPTEN)
    message(STATUS "Emscripten build")
elseif(ANDROID)
    message(STATUS "Android build")
elseif(APPLE)
    option(FIND_PACKAGE_FREEGLUT      "force find_package for FreeGLUT"  ON)
    option(FIND_PACKAGE_GLFW          "force find_package for GLFW"      OFF) 
    option(FIND_PACKAGE_GLEW          "force find_package for GLEW"      OFF)
else()
    option(FIND_PACKAGE_FREEGLUT      "force find_package for FreeGLUT"  OFF)
    option(FIND_PACKAGE_GLFW          "force find_package for GLFW"      OFF) 
    option(FIND_PACKAGE_GLEW          "force find_package for GLEW"      OFF)
endif()
#if(NOT EMSCRIPTEN AND NOT ANDROID)
#    option(FIND_PACKAGE_FREEGLUT      "force find_package for FreeGLUT"  OFF)
#    option(FIND_PACKAGE_GLFW          "force find_package for GLFW"      OFF) 
#    option(FIND_PACKAGE_GLEW          "force find_package for GLEW"      OFF)
#endif()

# Под Emscripten надобности в этой библиотеке нет
if(APPLE)
    option(FIND_PACKAGE_OPENAL        "force find_package for OpenAL"    ON)
    option(FIND_PACKAGE_FREETYPE      "force find_package for FreeType"  OFF)
elseif(NOT EMSCRIPTEN)
    option(FIND_PACKAGE_OPENAL        "force find_package for OpenAL"    OFF)
    option(FIND_PACKAGE_FREETYPE      "force find_package for FreeType"  OFF)
endif()

option(FIND_PACKAGE_BOX2D         "force find_package for Box2D"     OFF)
option(FIND_PACKAGE_GLM           "force find_package for glm"       OFF)
option(FIND_PACKAGE_LUA           "force find_package for Lua"       OFF)
option(FIND_PACKAGE_LIBPNG        "force find_package for libpng"    OFF)
option(FIND_PACKAGE_OGG           "force find package for Ogg"       OFF)
option(FIND_PACKAGE_VORBIS        "force find package for Vorbis"    OFF)

# Под Emscripten и Android буст мне не нужен, а ...
if(NOT EMSCRIPTEN AND NOT ANDROID AND NOT MINGW AND NOT MSYS)
    option(FIND_PACKAGE_BOOST         "force find_package for boost"     OFF)
endif()

# ... под MinGW или MSYS буст только через find_package
if(MINGW OR MSYS)
    option(FIND_PACKAGE_BOOST         "force find_package for boost" ON)
endif()

# Под Emscripten и Android врапперы пока не собираем
if(NOT EMSCRIPTEN AND NOT ANDROID)
    option(WITH_WRAPPERS              "Wrapper"                         ON)
    option(WITH_LUA_WRAPPER           "Lua wrapper"                     ON)
    option(WITH_PYTHON_WRAPPER        "Python wrapper"                  ON)
    
    option(WITH_GANIMEDE              "Build Ganimede"                  OFF)
    option(WITH_GAME_PLAYER           "Build with c++ game player"      ON)
    
    option(WITH_GLFW_PYTHON_WRAPPER   "Build GLFW Python Wrapper"       ON)
    option(WITH_GLFW_LUA_WRAPPER      "Build GLFW Lua Wrapper"          ON)
    
    option(WITH_GLEW_PYTHON_WRAPPER   "Build GLEW Python Wrapper"       ON)
    option(WITH_GLEW_LUA_WRAPPER      "Build GLEW Lua Wrapper"          ON)
    
    option(WITH_GL_PYTHON_WRAPPER     "Build GL Python Wrapper"         ON)
    option(WITH_GL_LUA_WRAPPER        "Build GL Lua Wrapper"            ON)
    
    option(WITH_GLM_PYTHON_WRAPPER    "Build glm Python Wrapper"        ON)
    option(WITH_GLM_LUA_WRAPPER       "Build glm Lua Wrapper"           ON)
    
    option(WITH_BOX2D_PYTHON_WRAPPER  "Build Box2D Python Wrapper"      ON)
    option(WITH_BOX2D_LUA_WRAPPER     "Build Box2D Lua Wrapper"         ON)
endif()

# Под Android эти программы не собираем
if(NOT ANDROID)
    option(WITH_TEST_PROGRAMS         "Build test programs Test1, Test2" ON)
endif()

# Под Emscripten и Android это не актуально
if(NOT EMSCRIPTEN OR NOT ANDROID)
    set(OPENGL_WINDOW_SYSTEM "FreeGLUT" CACHE STRING "Select a OpenGL window system")
    set_property(CACHE OPENGL_WINDOW_SYSTEM PROPERTY STRINGS "FreeGLUT" "GLFW")
endif()

# find OpenGL
if(NOT ANDROID)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/install)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/lib)

if(MINGW OR MSYS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")

elseif(EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-warn-absolute-paths")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

elseif(ANDROID)
else()
endif()

add_subdirectory(3rdparty)

include_directories(
    3rdparty/json/src
    3rdparty/lodepng
    
    modules/Jupiter/include
    modules/Ganymede/include
    
    ${3RDPARTY_INSTALL}/include
)

link_directories(${3RDPARTY_INSTALL}/lib)

# Libraries sets

# Lua
unset(LUA_LIB)
if(FIND_PACKAGE_LUA)
    find_package(Lua)
    include_directories(${LUA_INCLUDE_DIR})
    set(LUA_LIB ${LUA_LIB} ${LUA_LIBRARIES})
else()
    set(LUA_LIB ${LUA_LIB} lua)
endif()

# GLEW
unset(GLEW_LIB)
if(FIND_PACKAGE_GLEW)
    find_package(GLEW REQUIRED)
    set(GLEW_LIB ${GLEW_LIB} ${GLEW_LIBRARIES})
else()
    if(MINGW OR MSYS)
        set(GLEW_LIB ${GLEW_LIB} glew32 glew32mx)
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        set(GLEW_LIB ${GLEW_LIB} GLEW GLEWmx)
    endif()
endif()

# FreeGLUT and GLFW
unset(GL_WINDOW)
if(NOT EMSCRIPTEN AND NOT ANDROID)
    # FreeGLUT window system
    if(FIND_PACKAGE_FREEGLUT)
        find_package(GLUT REQUIRED)
        include_directories(${GLUT_INCLUDE_DIR})
        list(APPEND GL_WINDOW ${GLUT_LIBRARIES})
    else()
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            list(APPEND GL_WINDOW glut)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            list(APPEND GL_WINDOW freeglut)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
            list(APPEND GL_WINDOW glut)
        else()
            message(FATAL_ERROR "error")
        endif()
    endif()

    # GLFW window system
    if(FIND_PACKAGE_GLFW)
        find_package(GLFW REQUIRED)
        include_directories(${GLFW_INCLUDE_DIR})
        list(APPEND GL_WINDOW ${GLFW_LIBRARIES})
    else()
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            list(APPEND GL_WINDOW glfw)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            list(APPEND GL_WINDOW glfw3)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
            list(APPEND GL_WINDOW glfw)
        else()
            message(FATAL_ERROR "error")
        endif()
    endif()
endif()

# GLM
if(FIND_PACKAGE_GLM)
    # find glm
    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

# Box2D
unset(BOX2D_LIB)
if(FIND_PACKAGE_BOX2D)
    find_package(Box2D REQUIRED)
    include_directories(${BOX2D_INCLUDE_DIR})
    list(APPEND BOX2D_LIB ${BOX2D_LIBRARIES})
else()
    list(APPEND BOX2D_LIB Box2D)
endif()

# Boost
set(BOOST_LIB)
if(WITH_GAME_PLAYER)
    if(FIND_PACKAGE_BOOST)
    
        if(MINGW)
        elseif(EMSCRIPTEN)
        else()
        endif()
    
        set(Boost_USE_STATIC_LIBS    ON)
        set(Boost_USE_MULTITHREADED  ON)
        if(MINGW)
            set(Boost_COMPILER -mgw48)
        else()
            set(Boost_COMPILER -gcc)
        endif()
        
        find_package(Boost 1.53.0 REQUIRED system filesystem program_options)

        include_directories(${Boost_INCLUDE_DIRS})
        list(APPEND BOOST_LIB ${Boost_LIBRARIES})
    else()
        list(APPEND BOOST_LIB 
            boost_filesystem
            boost_program_options
            boost_system
        )
    endif()
endif()

# PNG
unset(PNG_LIB)
if(FIND_PACKAGE_LIBPNG)
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIRS})
    list(APPEND PNG_LIB ${PNG_LIBRARIES})
else()
endif()

# OpenAL
unset(OPENAL_LIB)
if(FIND_PACKAGE_OPENAL)
    find_package(OpenAL REQUIRED)
    include_directories(${OPENAL_INCLUDE_DIR})
    list(APPEND OPENAL_LIB ${OPENAL_LIBRARY})
else()
    if(MINGW OR MSYS)
        list(APPEND OPENAL_LIB OpenAL32)
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
        list(APPEND OPENAL_LIB openal)
    else()
        list(APPEND OPENAL_LIB openal)
    endif()
endif()

# FreeType
unset(FREETYPE_LIB)
if(FIND_PACKAGE_FREETYPE)
    find_package(Freetype REQUIRED)
    include_directories(${FREETYPE_INCLUDE_DIRS})
    list(APPEND FREETYPE_LIB ${OPENAL_LIBRARY})
else()
    include_directories(${3RDPARTY_INSTALL}/include/freetype2)
    
    list(APPEND FREETYPE_LIB freetype)
endif()

# Ogg
unset(OGG_LIB)
if(FIND_PACKAGE_OGG)
else()
    list(APPEND OGG_LIB ogg)
endif()

# Vorbis
unset(VORBIS_LIB)
if(FIND_PACKAGE_VORBIS)
else()
    list(APPEND VORBIS_LIB vorbis)
endif()

add_definitions(-std=c++11)

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

