/*
 * Camera.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: pavel
 */

#include "Jupiter/Ref.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Transform.h"

#include "Jupiter/Camera.h"

namespace jupiter {

using namespace std;
using namespace glm;

Camera::Camera(Transform* transform, Ortho ortho) :
    _transform(transform) {
}

Camera::Camera(Transform* transform, Perspective perspective) :
    _transform(transform), _projection(
        glm::perspective(perspective.fovy, perspective.aspect, perspective.near, perspective.far)) {
}

Camera::Camera(Camera const& camera) {
    *this = camera;
    _nodes.clear();
    for (auto i : camera._nodes) {
        auto copy = i->clone();
        copy->setParent(this);
        _nodes.emplace_back(copy);
    }
}

Camera* Camera::clone() {
    return new Camera(*this);
}

Camera* Camera::accept(NodeVisitor* nv) {
    jassert(nv, "visitor is nullptr");
    if (_visible) {
        nv->push(this);
        nv->visit(this);
        for (auto i : _nodes) {
            jassert(i, "invalid node");
            i->accept(nv);
        }
        nv->pop(this);
    }
    return this;
}

mat4 Camera::getProjectionMatrix() const {
    return _projection;
}

mat4 Camera::getViewMatrix() const {
    jassert(_transform, "no transform");
    return glm::translate( { }, _transform->getPosition()) * glm::mat4_cast(_transform->getRotation());
}

}  // namespace jupiter

