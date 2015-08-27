/*
 * Out.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#include <iostream>

#include "Out.h"

using namespace std;

Out::Out() {
}

Out::~Out() {
}

void Out::add(In* in) {
    _ins.push_back(in);
}

void Out::remove(In* in) {
    in->outOff(this);
    _ins.remove(in);
}

void Out::notify() {
    for (auto i : _ins)
        i->update();
}
