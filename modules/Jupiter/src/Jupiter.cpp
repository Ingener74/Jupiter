/*
 * Jupiter.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: pavel
 */

#include <string>

#include <GL/glew.h>

#include "Jupiter.h"

namespace jupiter {

using namespace std;

void initJupiter() {

    /*
     * Eсли появляется ошибка: Missing GL version, значит для текущего окна контекст не установлен,
     * сделай makeCurrentContext
     */

    auto result = glewInit();
    jassert(GLEW_OK == result, string {"glewInit error: "} + reinterpret_cast<const char*>(glewGetErrorString(result)));
}

void deinitJupiter() {
}

}  // namespace jupiter

