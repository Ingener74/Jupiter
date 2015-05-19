/*
 * MoveListener.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <iostream>
#include "Jupiter/MoveListener.h"

namespace jupiter {

MoveListener::MoveListener() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

MoveListener::~MoveListener() {
}

void MoveListener::move(float x, float y, float z) {
}

} /* namespace jupiter */
