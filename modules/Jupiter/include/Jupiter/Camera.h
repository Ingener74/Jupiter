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

//struct Perspective {
//    Perspective (float fovy, float aspect, float near, float far) :
//        fovy(fovy), aspect(aspect), near(near), far(far) {
//    }
//    float fovy;
//    float aspect;
//    float near;
//    float far;
//};
//
//struct Ortho{
//    float left, right, top, bottom;
//    float _near;
//
//};

class Camera {
public:
    Camera(float fovy,
        float width, float height,
        float near, float far,
        float eyex, float eyey, float eyez,
        float centerx, float centery, float centerz,
        float upx, float upy, float upz);
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
