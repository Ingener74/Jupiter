/*
 * In.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include "In.h"
#include "Out.h"

using namespace std;

In::In() {
}

In::~In() {
}

void In::update() {
    if(!_out)
        return;
    auto data = _out->getData<int>();
}

void In::outOff(Out* out) {
    if (out != _out)
        throw runtime_error("not this out");
    _out = nullptr;
}
