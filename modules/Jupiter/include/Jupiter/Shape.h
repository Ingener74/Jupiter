/*
 * Shape.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef SWIG
    namespace jupiter {
        #pragma SWIG nowarn=312
    }  // namespace jupiter
#else
    #include <map>
    #include <string>
    #include <vector>
    #include <cstdint>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
#endif

namespace jupiter
{

/*
 * {
 *     "shaderUniforms":{
 *         "texture0":"",
 *         "model":"",
 *     },
 *     "shaderAttribs":[
 *         "attribVertex":3,
 *         "attribTexCoord":2,
 *         "attribColor":4
 *     ],
 *     "data":[
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f,
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f,
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f
 *     ]
 * }
 */

class VertexComponent {
public:
    VertexComponent(uint32_t size = 0, float* offset = nullptr) :
        size(size), offset(offset) {

        // Bind VBO

    }
    virtual ~VertexComponent() {

        // Unbind VBO
    }

    uint32_t getSize() const {
        return size;
    }

    const float* getOffset() const {
        return offset;
    }

private:
    uint32_t size = 0;
    float* offset = nullptr;
};

class Shape
{
public:
    enum Type
    {
        TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, LINE_STRIP
    };

    Shape() = default;
    Shape(const std::vector<float>& data, Type type);
    virtual ~Shape() = default;

    uint32_t getVertexCount() const;
    uint32_t getStride() const;
    Type getType() const;

    void test(const glm::mat4& mvp);

    const VertexComponent& getComponent(const std::string& name);

protected:
    std::vector<float> data;
//    GLuint vbo = 0;
//    uint32_t stride = 0;
    std::map<std::string, VertexComponent> components;
    Type type = TRIANGLE_STRIP;
};

} /* namespace jupiter */

#endif /* SHAPE_H_ */
