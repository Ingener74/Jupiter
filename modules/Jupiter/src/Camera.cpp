/*
 * Camera.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: pavel
 */

#include "Jupiter/Camera.h"

namespace jupiter {

using namespace std;
using namespace glm;

Camera::Camera(float fovy,
    float width, float height,
    float near, float far,
    float eyex, float eyey, float eyez,
    float centerx, float centery, float centerz,
    float upx, float upy, float upz) :
        _projection(glm::perspective(fovy, width / height, near, far)),
        _view(lookAt(vec3{eyex, eyey, eyez}, vec3{centerx, centery, centerz}, vec3{upx, upy, upz}))
{
}

Camera::Camera(const glm::mat4& projection, const glm::mat4& view) :
    _projection(projection), _view(view) {
}

Camera::~Camera() {
}

const glm::mat4& Camera::getProjectionMatrix() const {
    return _projection;
}

const glm::mat4& Camera::getViewMatrix() const {
    return _view;
}

void Camera::setViewMatrix(const glm::mat4& view) {
    _view = view;
}

}  // namespace jupiter

