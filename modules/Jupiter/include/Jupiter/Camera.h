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

#endif

namespace jupiter {

#undef near
#undef far

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

struct Vec2 {
    Vec2(float x, float y) :
        x(x), y(y) {
    }
    float x, y;
};

struct Vec3 {
    Vec3(float x, float y, float z) :
        x(x), y(y), z(z) {
    }
    float x, y, z;
};

class Camera {
public:
    Camera(float fovy,
        float width, float height,
        float near, float far,
        float eyex, float eyey, float eyez,
        float centerx, float centery, float centerz,
        float upx, float upy, float upz);

    Camera(Ortho, Vec3, Vec3, Vec3){}
    Camera(Perspective, Vec3, Vec3, Vec3){}

    Camera(const glm::mat4& projection = {}, const glm::mat4& view = {});
    virtual ~Camera();

    const glm::mat4& getProjectionMatrix() const;
    const glm::mat4& getViewMatrix() const;

    void setViewMatrix(const glm::mat4&);

protected:
    glm::mat4 _projection, _view;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_ */
