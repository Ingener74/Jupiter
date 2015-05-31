/*
 * Camera.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Camera.h"

namespace jupiter {

using namespace std;
using namespace glm;

Camera::Camera(Ortho ortho, Vec3 eye, Vec3 center, Vec3 up) :
    _projection(glm::ortho(ortho.left, ortho.right, ortho.bottom, ortho.top, ortho.near, ortho.far)),
    _view(glm::lookAt(vec3{eye.x, eye.y, eye.z}, vec3{center.x, center.y, center.z}, vec3{up.x, up.y, up.z})) {
}

Camera::Camera(Perspective perspective, Vec3 eye, Vec3 center, Vec3 up) :
    _projection(glm::perspective(perspective.fovy, perspective.aspect, perspective.near, perspective.far)),
    _view(lookAt(vec3(eye.x, eye.y, eye.z), vec3(center.x, center.y, center.z), vec3(up.x, up.y, up.z))) {
}

Camera::Camera(glm::mat4 const& projection, glm::mat4 const& view) :
    _projection(projection), _view(view) {
}

Camera::~Camera() {
}

glm::mat4 const& Camera::getProjectionMatrix() const {
    return _projection;
}

glm::mat4 const& Camera::getViewMatrix() const {
    return _view;
}

void Camera::setViewMatrix(glm::mat4 const& view) {
    _view = view;
}

Camera* Camera::clone(Camera* camera) {
    jassert(camera, "node is invalid");
    *this = *camera;
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
        nv->pop();
    }
    return this;
}

}  // namespace jupiter

