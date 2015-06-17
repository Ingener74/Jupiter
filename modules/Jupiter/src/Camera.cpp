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

Camera::Camera(Ortho ortho) {
}

Camera::Camera(Perspective perspective) :
    _projection(glm::perspective(perspective.fovy, perspective.aspect, perspective.near, perspective.far)) {
}

mat4 Camera::getProjectionMatrix() const {
    return _projection;
}

mat4 Camera::getViewMatrix() const {
    jassert(_transform, "not transform");
    return glm::translate( { }, _transform->getPosition()) * glm::mat4_cast(_transform->getRotation());
}

void Camera::setViewMatrix(mat4 const& view) {
    jassert(false, "deprecated");
    _view = view;
}

Camera* Camera::clone(Camera* camera) {
    Ref<Camera>{camera};
    jassert(camera, "node is invalid");
    *this = *camera;
    return this;
}

Camera* Camera::setParent(Node* node) {
    _transform = dynamic_cast<Transform*>(node);
    jassert(_transform, "parent must be transform");
    return this;
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

}  // namespace jupiter

