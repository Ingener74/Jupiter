/*
 * KeyboardListener.cpp
 *
 *  Created on: May 19, 2015
 *      Author: pavel
 */

#include <iostream>
#include "Jupiter/Game.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/KeyboardListener.h"

namespace jupiter {

KeyboardListener::KeyboardListener() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

KeyboardListener::~KeyboardListener() {
}

void KeyboardListener::key(int keyCode) {
}

void KeyboardListener::key(Key key) {
}

} /* namespace jupiter */
