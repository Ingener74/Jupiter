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

#include "JupiterBox2d.h"
#include "Node.h"

namespace jupiter {

class NodeVisitor;

struct Ortho {
    Ortho(float left, float right, float top, float bottom, float near, float far) :
        left(left), right(right), top(top), bottom(bottom), near(near), far(far) {
    }
    float left, right, top, bottom, near, far;
};

struct Perspective {
    Perspective(float fovy, float aspect, float near, float far) :
        fovy(fovy), aspect(aspect), near(near), far(far) {
    }
    float fovy, aspect, near, far;
};

class Camera: virtual public Node {
public:
    Camera(Ortho, Vec3 eye, Vec3 center, Vec3 up);
    Camera(Perspective, Vec3 eye, Vec3 center, Vec3 up);

    Camera(glm::mat4 const& projection = { }, glm::mat4 const& view = { });
    virtual ~Camera();

    glm::mat4 const& getProjectionMatrix() const;
    glm::mat4 const& getViewMatrix() const;

    void setViewMatrix(glm::mat4 const&);

    virtual Camera* clone(Camera*);

    virtual Camera* accept(NodeVisitor* nv);

protected:
    glm::mat4 _projection, _view;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_ */
