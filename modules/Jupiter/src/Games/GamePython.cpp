/*
 * GamePython.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: pavel
 */

#include <sstream>

#include <python2.7/Python.h>

#include "Jupiter/File.h"
#include "Jupiter/Games/GamePython.h"

namespace jupiter {

using namespace std;

GamePython::GamePython(File* script) :
    GamePython(reinterpret_cast<const char*>(script->getBuffer().data())) {
}

GamePython::GamePython(const std::string& script) {
    Py_Initialize();
    PyRun_SimpleString(script.c_str());
}

GamePython::~GamePython() {
    Py_Finalize();
}

} /* namespace jupiter */
