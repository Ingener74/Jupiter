/*
 * NextSummer.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: pavel
 */

#include <iostream>

#include <Python.h>

#include "NextSummer.h"

namespace nextsummer {

using namespace std;

NextSummer::NextSummer(std::string const& s): _s(s) {
    cout << __PRETTY_FUNCTION__ << " " << _s << endl;
}

NextSummer::~NextSummer() {
    cout << __PRETTY_FUNCTION__ << " " << _s << endl;
}

void NextSummer::sayHelloNextSummer() {
    cout << "Hello, next summer" << endl;
}

void NextSummer::execPythonScript(const std::string& script) {
    Py_Initialize();
    PyRun_SimpleString(script.c_str());
    Py_Finalize();
}

} /* namespace nextsummer */
