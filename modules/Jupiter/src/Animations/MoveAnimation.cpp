/*
 * MoveAnimation.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#include "Jupiter/Node.h"
#include "Jupiter/MoveAnimation.h"

namespace jupiter {

MoveAnimation::MoveAnimation(glm::vec3 start, glm::vec3 end, float duration) :
    _start(start), _end(end), _duration(duration) {
}

MoveAnimation::~MoveAnimation() {
}

void MoveAnimation::update(float dt) {

    float x = _start.x + (_end.x - _start.x) / (_pastTime / _duration);
    float y = _start.y + (_end.y - _start.y) / (_pastTime / _duration);

    _node->setPosition(x, y, _node->getPositionZ());
    _pastTime += dt;
}

} /* namespace jupiter */
