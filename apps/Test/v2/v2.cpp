/*
 * v2.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

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
};

template<typename T>
class RangeVector{
    std::vector<RangeVector<T>> v;
public:
    RangeVector(){
    }
    virtual ~RangeVector(){}

    void push_back(const Range<T>& range){
        if(range.start >= range.end)
            throw invalid_argument("bad range");
        if(v.empty() && !range.start)
            throw invalid_argument("first range must start with 0");
        if (!v.empty() && v.back().end != range.begin)
            throw invalid_argument("error 2");

        v.push_back(range);
    }

    size_t full_size() const {
        return v.size();
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

struct MeshIn {

    struct Attribute {
        string attribute;
        vector<Range<vector<float>>> data;
    };
    struct Texture{
        GLuint textureId;
        GLuint unit;
    };
    struct Uniform {
        string                        uniform;
        vector<Range<Texture>>        textures;
    };

    int                               frames;

    vector<Attribute>                 attributesData;
    vector<Uniform>                   uniformsData;

    vector<Range<vector<uint16_t>>>   indeces;
    vector<Range<GLenum>>             drawModes;
};

/*
MeshIn boxMeshData{
    3,
    {
        {
            "pos",
            {
                { 0, 3, {0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f,  } }
            }
        },
        {
            "texcoord",
            {
                { 0, 1, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  } },
                { 1, 2, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  } },
                { 2, 3, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  } },
            }
        }
    },
    {
        {
            "texture",
            {
                { 0, 3, {3, 0} }
            }
        },
        {
            "bump",
            {
                { 0, 3, {5, 0} }
            }
        }
    },
    {
        { 0, 3, {0, 1, 2, 3} }
    },
    {
        { 0, 3, GL_TRIANGLE_STRIP }
    }
};
*/

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

class Mesh {
public:
    Mesh(Program* shaderProgram, const MeshIn & mesh) {
    }

    Mesh() {
    }

    virtual ~Mesh() {
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

    /*
     * frames          0            1            3
     *
     * vao             5            6            7
     *
     * pos             12           12           12
     * texcoord        13           14           16
     *
     * indexes         11           11           11
     *
     * texture
     */
};

unique_ptr<Program> coloredSh, texturedSh;
unique_ptr<Mesh> root, bgMesh, groundMesh, boxMesh;

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

