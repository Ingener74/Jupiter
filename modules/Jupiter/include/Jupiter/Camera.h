/*
 * Camera.h
 *
 *  Created on: Mar 29, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_

class Camera {
public:
    Camera(float eye[3], float center[3], float up[3]);
    virtual ~Camera();

    glm::mat4 getCameraMatrix() const;

protected:
    float eye[3], center[3], up[3];
};

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CAMERA_H_ */
