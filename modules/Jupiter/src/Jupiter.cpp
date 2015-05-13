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
    if (result != GLEW_OK) {
        auto resultString = reinterpret_cast<const char*>(glewGetErrorString(result));
        throw JupiterError(string { "glewInit error: " } + resultString);
    }

}

}  // namespace jupiter

