/*
 * Jupiter.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: pavel
 */

#include <string>

#ifdef ANDROID
    #include <GLES2/gl2.h>
#else
    #include <GL/glew.h>
#endif

#include "Jupiter.h"

namespace jupiter {

using namespace std;

void startJupiter() {

    /*
     * Eсли появляется ошибка: Missing GL version, значит для текущего окна контекст не установлен,
     * сделай makeCurrentContext
     */

#ifndef ANDROID
    auto result = glewInit();
    jassert(GLEW_OK == result, string {"glewInit error: "} + reinterpret_cast<const char*>(glewGetErrorString(result)));
#endif
}

void endJupiter() {
}

}  // namespace jupiter

