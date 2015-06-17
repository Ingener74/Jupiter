/*
 * ImageShape.cpp
 *
 *  Created on: 20 марта 2015 г.
 *      Author: pavel
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jupiter/Ref.h"
#include "Jupiter/Tools.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/ImageShape.h"

namespace jupiter {

using namespace std;
using namespace glm;

ImageShape::ImageShape(Image* image, float scale) {

    Ref<Image>{image};

    /*
     * -w/2                  w/2
     *
     *   0                   1     h/2     texW
     *
     *
     *   2                   3    -h/2
     *
     *
     *
     *
     *   texH
     */

    float h = image->getHeight(), w = image->getWidth();
    float l = Tools::upperPowerOfTwo(std::max(h, w));

    float z = 0.f;

    vec3
    p0{scale * -w/2, scale *  h/2, z},
    p1{scale *  w/2, scale *  h/2, z},
    p2{scale * -w/2, scale * -h/2, z},
    p3{scale *  w/2, scale * -h/2, z};

    vec2
    t0{w/l, 0.f},
    t1{0.f, 0.f},
    t2{w/l, h/l},
    t3{0.f, h/l};

    data = {
        // 2 1 0
        p2.x, p2.y, p2.z,  t2.x, t2.y,
        p1.x, p1.y, p1.z,  t1.x, t1.y,
        p0.x, p0.y, p0.z,  t0.x, t0.y,
        // 1 2 3
        p1.x, p1.y, p1.z,  t1.x, t1.y,
        p2.x, p2.y, p2.z,  t2.x, t2.y,
        p3.x, p3.y, p3.z,  t3.x, t3.y,
    };

    components = { {"VertexPosition", {3, &data[0]}}, {"VertexTexCoord", {2, &data[3]}}};

    vertexCount = 6;
    stride = 5 * sizeof(float);

    type = TRIANGLES;
}

ImageShape::~ImageShape() {
}

} /* namespace jupiter */
