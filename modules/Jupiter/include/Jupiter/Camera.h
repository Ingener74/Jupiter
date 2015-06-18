/*
 * Camera.h
 *
 *  Created on: Mar 29, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_

#ifdef SWIG
#else

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>

    #undef near
    #undef far

#endif

#include "Node.h"

namespace jupiter {

class NodeVisitor;
class Transform;

struct Ortho {
    Ortho(float left = -1, float right = 1, float top = 1, float bottom = -1, float near = -1, float far = 1) :
        left(left), right(right), top(top), bottom(bottom), near(near), far(far) {
    }
    float left, right, top, bottom, near, far;
};

struct Perspective {
    Perspective(float fovy = 45., float aspect = 4. / 3., float near = 1., float far = 1000.) :
        fovy(fovy), aspect(aspect), near(near), far(far) {
    }
    float fovy, aspect, near, far;
};

class Camera: public Node {
public:
    Camera() = default;
    Camera(Transform*, Ortho);
    Camera(Transform*, Perspective);
    Camera(Camera const&);

    virtual ~Camera() = default;

    virtual Camera* clone();

    virtual Camera* accept(NodeVisitor* nv);

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

protected:
    Transform* _transform = nullptr;
    glm::mat4 _projection, _view;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_ */
