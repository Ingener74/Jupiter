/*
 * v2.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

#include <functional>

#include "main.h"
#include "Attribute.h"
#include "Uniform.h"
#include "Program.h"

using namespace std;
using namespace glm;

/*

Array of Structure
[{pos, col, texcoord, normal}, {pos, col, texcoord, normal}, {pos, col, texcoord, normal}, ... ]

Structure of Arrays
{
    [{pos}     , {pos}     , {pos}     , ... ],
    [{col}     , {col}     , {col}     , ... ],
    [{texcoord}, {texcoord}, {texcoord}, ... ],
    [{normal}  , {normal}  , {normal}  , ... ],
}

*/

template<typename T>
struct Range {
    size_t start, end;
    T data;

    bool inRange(int32_t i) const {
        return i >= start && i < end;
    }

    size_t size() const{
        return end - start;
    }

    size_t operator+(const Range& r) {
        return size() + r.size();
    }

};

template<typename T>
class RangeVector{
    std::vector<Range<T>> v;
public:
    RangeVector(size_t size): v(size) {
    }
    virtual ~RangeVector(){}

    void push_back(const Range<T>& range){
        if(range.start >= range.end)
            throw invalid_argument("bad range");
        if(v.empty() && !range.start)
            throw invalid_argument("first range must start with 0");
        if (!v.empty() && v.back().end != range.start)
            throw invalid_argument("bad range 2");

        v.push_back(range);
    }

    size_t size() const {
        return v.size();
    }
    size_t full_size() const {
        return accumulate(v.begin(), v.end(), 0, plus<Range<T>>());
    }

    Range<T>& at(size_t index) {
        return v.at(index);
    }

    T& at_full(size_t index) {
        auto it = v.begin();
        while (!it->inRange(index))
            ++it;
        return it->data;
    }
};



string vertex_color = R"(

#version 330

uniform mat4 projection, view, model;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 color_;

void main(){
    gl_Position = projection * view * model * position;
    color_ = color;
}

)", fragment_color = R"(

#version 330

in vec4 color_;

out vec4 fragColor;

void main(){
    fragColor = color_;
}

)";

template<typename T>
using Frames = vector<T>;

using VertexData = vector<float>;
using Elements   = vector<uint16_t>;

using DrawMode   = GLuint;

struct Mesh {
    int                               frames;

    struct Attribute {
        string attribute;
        Frames<VertexData> data;
    };
    vector<Attribute>                 attributesData;

    struct Texture{
        GLuint textureId;
        GLuint unit;
    };
    struct Uniform {
        string                        uniform;
        Frames<Texture>               textures;
    };
    vector<Uniform>                   uniformsData;

    Frames<Elements>                  elements;
    Frames<DrawMode>                  drawModes;
};

Mesh boxMeshData{
    3,
    {
        {
            "pos",
            {
                {0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,  },
                {0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,  },
                {0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,  },
            }
        },
        {
            "texcoord",
            {
                {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  },
                {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  },
                {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  },
            }
        }
    },
    {
        {
            "texture",
            {
                {3, 0},
                {3, 0},
                {3, 0},
            }
        },
        {
            "bump",
            {
                {5, 0},
                {5, 0},
                {5, 0},
            }
        }
    },
    {
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    },
    {
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_STRIP,
    }
};

class GLBuffer {
public:
    virtual ~GLBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
};

class VaoBuffer: public GLBuffer {
    GLuint buffer;

    VaoBuffer(const VaoBuffer&);
    VaoBuffer& operator=(const VaoBuffer&);
public:
    VaoBuffer() {
        glGenVertexArrays(1, &buffer);
    }
    virtual ~VaoBuffer() {
        glDeleteVertexArrays(1, &buffer);
    }
    virtual void bind() {
        glBindVertexArray(buffer);
    }
    virtual void unbind() {
        glBindVertexArray(0);
    }
};

class ArrayBuffer: public GLBuffer {
    GLuint buffer;

    ArrayBuffer(const VaoBuffer&);
    ArrayBuffer& operator=(const VaoBuffer&);
public:
    ArrayBuffer(const vector<float>& array) {
        glGenBuffers(1,  &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(float), array.data(), GL_STATIC_DRAW);
    }
    virtual ~ArrayBuffer() {
        glDeleteBuffers(1, &buffer);
    }
    virtual void bind(){
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }
    virtual void unbind(){}
};

class ElementBuffer: public GLBuffer {
    GLuint buffer, bufferCount;

    ElementBuffer(const VaoBuffer&);
    ElementBuffer& operator=(const VaoBuffer&);
public:
    ElementBuffer(const vector<uint16_t>& elements): buffer(0), bufferCount(elements.size()){
        glGenBuffers(1,  &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint16_t), elements.data(), GL_STATIC_DRAW);
    }
    virtual ~ElementBuffer(){
        glDeleteBuffers(1, &buffer);
    }
    virtual void bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    }
    virtual void unbind(){}

    GLsizei getElementsCount() const{
        return bufferCount;
    }
};

class Frame {
public:
    GLenum drawMode;

    VaoBuffer* vao;
    vector<ArrayBuffer*> attribBuffers;
    ElementBuffer* vio;
};

class Node {
public:
    Node(Program* shaderProgram, const Mesh & mesh) {

//        for (size_t frame = 0; frame < mesh.frames; ++frame) {
//            vertexArrays.push_back(make_unique_<VaoBuffer>());
//        }
//
//        dataArrays.resize(mesh.attributesData.size());
//        for(size_t attrib = 0; attrib < mesh.attributesData.size(); ++attrib){
//
//            auto attribId = shaderProgram->getAttribute(mesh.attributesData.at(attrib).attribute).attribute;
//
//            for(size_t i = 0; i < mesh.attributesData.at(attrib).data.size(); ++i){
//                dataArrays.
//            }
//        }

    }

    Node() {
    }

    virtual ~Node() {
    }

    void draw(size_t frame = 0, const vector<mat4>& models = { }) {

        frames.at(frame).vao->bind();

        glDrawElements(frames.at(frame).drawMode, frames.at(frame).vio->getElementsCount(), GL_UNSIGNED_SHORT, nullptr);

        frames.at(frame).vao->unbind();
    }

    size_t getFrameCount() const {
        return frames.size();
    }

protected:
    vector<Frame> frames;

    // frames
    vector<unique_ptr<VaoBuffer>> vertexArrays;

    // attrib  // frame ranges
    vector<    vector<         unique_ptr<ArrayBuffer>>> dataArrays;

    // frame ranges
    vector<         unique_ptr<ElementBuffer>> elementArray;
};

unique_ptr<Program> coloredSh, texturedSh;
unique_ptr<Node> button;

mat4 proj, view;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
//    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void init() {
    coloredSh = make_unique_<Program>(vertex_color, fragment_color);
    cout << "colored shader: " << *coloredSh << endl;
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glFlush();
    glutSwapBuffers();
}

void deinit() {
}

