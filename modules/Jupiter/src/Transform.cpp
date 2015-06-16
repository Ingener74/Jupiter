/*
 * Transform.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: pavel
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Jupiter/MoveListener.h"
#include "Jupiter/ScaleListener.h"
#include "Jupiter/RotationListener.h"

#include "Jupiter/Transform.h"

namespace jupiter {

using namespace std;
using namespace glm;

Transform::Transform() {
}

Transform::Transform(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale) :
    _position(position), _scale(scale), _rotation(glm::rotate(glm::quat { }, angle, rotation)) {
}

Transform::~Transform() {
}

float Transform::getRotationX() const {
    return glm::axis(_rotation).x;
}

float Transform::getRotationY() const {
    return glm::axis(_rotation).y;
}

float Transform::getRotationZ() const {
    return glm::axis(_rotation).z;
}

float Transform::getRotationAngle() const {
    return glm::angle(_rotation);
}

Transform* Transform::setRotation(float x, float y, float z, float angle) {
    _rotation = glm::rotate(quat{}, angle, vec3(x, y, z));
    if (_rotationListener)
        _rotationListener->rotate(x, y, z, angle);
    return this;
}

Transform* Transform::setRotationX(float angle) {
    return setRotation(1.f, 0.f, 0.f, angle);
}

Transform* Transform::setRotationY(float angle) {
    return setRotation(0.f, 1.f, 0.f, angle);
}

Transform* Transform::setRotationZ(float angle) {
    return setRotation(0.f, 0.f, 1.f, angle);
}

Transform* Transform::rotate(float x, float y, float z, float angle) {
    _rotation = glm::rotate(_rotation, angle, vec3(x, y, z));
    if (_rotationListener)
        _rotationListener->rotate(x, y, z, angle);
    return this;
}

Transform* Transform::rotateX(float angle) {
    return rotate(1.f, 0.f, 0.f, angle);
}

Transform* Transform::rotateY(float angle) {
    return rotate(0.f, 1.f, 0.f, angle);
}

Transform* Transform::rotateZ(float angle) {
    return rotate(0.f, 0.f, 1.f, angle);
}

float Transform::getPositionX() const {
    return _position.x;
}

float Transform::getPositionY() const {
    return _position.y;
}

float Transform::getPositionZ() const {
    return _position.z;
}

Transform* Transform::setPosition(float x, float y, float z) {
    _position.x = x;
    _position.y = y;
    _position.z = z;
    if (_moveListener)
        _moveListener->move(_position.x, _position.y, _position.z);
    return this;
}

Transform* Transform::setPositionX(float x) {
    return setPosition(x, 0.f, 0.f);
}

Transform* Transform::setPositionY(float y) {
    return setPosition(0.f, y, 0.f);
}

Transform* Transform::setPositionZ(float z) {
    return setPosition(0.f, 0.f, z);
}

Transform* Transform::translate(float x, float y, float z) {
    _position.x += x;
    _position.y += y;
    _position.z += z;
    if (_moveListener)
        _moveListener->move(_position.x, _position.y, _position.z);
    return this;
}

Transform* Transform::translateX(float x) {
    return translate(x, 0.f, 0.f);
}

Transform* Transform::translateY(float y) {
    return translate(0.f, y, 0.f);
}

Transform* Transform::translateZ(float z) {
    return translate(0.f, 0.f, z);
}

float Transform::getScaleX() const {
    return _scale.x;
}

float Transform::getScaleY() const {
    return _scale.y;
}

float Transform::getScaleZ() const {
    return _scale.z;
}

Transform* Transform::setScale(float x, float y, float z) {
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
    if (_scaleListener)
        _scaleListener->scale(_scale.x, _scale.y, _scale.z);
    return this;
}

Transform* Transform::setScaleF(float scale) {
    return setScale(scale, scale, scale);
}

Transform* Transform::setScaleX(float x) {
    return setScale(x, 0.f, 0.f);
}

Transform* Transform::setScaleY(float y) {
    return setScale(0.f, y, 0.f);
}

Transform* Transform::setScaleZ(float z) {
    return setScale(0.f, 0.f, z);
}

Transform* Transform::scale(float x, float y, float z) {
    _scale.x *= x;
    _scale.y *= y;
    _scale.z *= z;
    if (_scaleListener)
        _scaleListener->scale(_scale.x, _scale.y, _scale.z);
    return this;
}

Transform* Transform::scaleF(float s) {
    return scale(s, s, s);
}

Transform* Transform::scaleX(float x) {
    return scale(x, 0.f, 0.f);
}

Transform* Transform::scaleY(float y) {
    return scale(0.f, y, 0.f);
}

Transform* Transform::scaleZ(float z) {
    return scale(0.f, 0.f, z);
}

Transform* Transform::setMoveListener(MoveListener* moveListener) {
    jassert(moveListener, "move listener is nullptr");
    _moveListener = moveListener;
    _moveListener->setNode(this);
    return this;
}

MoveListener* Transform::getMoveListener() {
    jassert(_moveListener, "no move listener");
    return _moveListener.get();
}

Transform* Transform::setScaleListener(ScaleListener* listener) {
    jassert(listener, "scale listener is nullptr");
    _scaleListener = listener;
    _scaleListener->setNode(this);
    return this;
}

ScaleListener* Transform::getScaleListener() {
    jassert(_scaleListener, "no scale listener");
    return _scaleListener.get();
}

Transform* Transform::setRotationListener(RotationListener* listener) {
    jassert(listener, "rotation listener is nullptr");
    _rotationListener = listener;
    _rotationListener->setNode(this);
    return this;
}

RotationListener* Transform::getRotationListener() {
    jassert(_rotationListener, "rotation listener is nullptr");
    return _rotationListener.get();
}

glm::mat4 Transform::getModel() const {
    return glm::translate( { }, _position) * glm::mat4_cast(_rotation) * glm::scale( { }, _scale);
}

} /* namespace jupiter */

