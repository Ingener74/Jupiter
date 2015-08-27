/*
 * In.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#include <iostream>

#include "In.h"

using namespace std;

In::In() {
}

In::~In() {
}

void In::update() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void In::outOff(Out* out) {
    if (out != _out)
        throw runtime_error("not this out");
    _out = nullptr;
}
