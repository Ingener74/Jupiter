/*
 * Transform.h
 *
 *  Created on: Jun 16, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_TRANSFORM_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_TRANSFORM_H_

#ifdef SWIG
    #pragma SWIG nowarn=362
#else
    #include "Ref.h"
#endif

#include "Node.h"

namespace jupiter {

class MoveListener;
class ScaleListener;
class RotationListener;

class Transform: public Node {
public:
    Transform();
    virtual ~Transform();

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;
    float getRotationAngle() const;

    virtual Transform* setRotation(float x, float y, float z, float angle);
    Transform* setRotationX(float angle);
    Transform* setRotationY(float angle);
    Transform* setRotationZ(float angle);

    virtual Transform* rotate(float x, float y, float z, float angle);
    Transform* rotateX(float angle);
    Transform* rotateY(float angle);
    Transform* rotateZ(float angle);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    virtual Transform* setPosition(float x, float y, float z);
    Transform* setPositionX(float x);
    Transform* setPositionY(float y);
    Transform* setPositionZ(float z);

    virtual Transform* translate(float x, float y, float z);
    Transform* translateX(float x);
    Transform* translateY(float y);
    Transform* translateZ(float z);

    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    virtual Transform* setScale(float x, float y, float z);
    Transform* setScaleF(float scale);
    Transform* setScaleX(float x);
    Transform* setScaleY(float y);
    Transform* setScaleZ(float z);

    virtual Transform* scale(float x, float y, float z);
    Transform* scaleF(float s);
    Transform* scaleX(float x);
    Transform* scaleY(float y);
    Transform* scaleZ(float z);

    Transform* setMoveListener(MoveListener*);
    MoveListener* getMoveListener();

    Transform* setScaleListener(ScaleListener*);
    ScaleListener* getScaleListener();

    Transform* setRotationListener(RotationListener*);
    RotationListener* getRotationListener();

    glm::mat4 getModel() const;

private:
    glm::vec3               _position           = {0.f, 0.f, 0.f};
    glm::vec3               _scale              = {1.f, 1.f, 1.f};
    glm::quat               _rotation           = glm::rotate(glm::quat{}, 0.f, glm::vec3{0.f, 0.f, 1.f});

    Ref<MoveListener>       _moveListener;
    Ref<ScaleListener>      _scaleListener;
    Ref<RotationListener>   _rotationListener;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_TRANSFORM_H_ */
