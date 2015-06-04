/*
 * MoveAnimation.h
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_MOVEANIMATION_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_MOVEANIMATION_H_

#ifdef SWIG
#else
    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
#endif

#include "Animation.h"

namespace jupiter {

class MoveAnimation: public Animation {
public:
    MoveAnimation(glm::vec3 start, glm::vec3 end, float durationInSec);
    virtual ~MoveAnimation();

    virtual void update(float dt);

protected:
    glm::vec3 _start, _end;
    float _duration = 0.f, _pastTime = 0.f;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_MOVEANIMATION_H_ */
