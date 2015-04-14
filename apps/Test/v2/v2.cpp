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
struct Range {
    int32_t start, end;
    T data;

    bool inRange(int32_t i) const {
        return i >= start && i < end;
    }
};

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
public:
};

class VboBuffer: public GLBuffer {
public:
};

class VioBuffer: public GLBuffer {
public:
    GLsizei getElementsCount() const;
};

class Frame {
public:
    GLenum drawMode;

    VaoBuffer* vao;
    vector<VboBuffer> attribBuffers;
    VioBuffer* vio;
};

class Mesh {
public:
    Mesh(Program* shaderProgram, const MeshIn & mesh){

//        vaos = vector<GLuint>(mesh.frames);
//
//        glGenVertexArrays(vaos.size(), vaos.data());
//
//        for(size_t i = 0; i < mesh.frames; ++i){
//
//            glBindVertexArray(vaos.at(i));
//
//            for (size_t j = 0; j < attributes.size(); ++j)
//                bindBuffer(shaderProgram, mesh, j, i);
//
//            bindIndexBuffer(shaderProgram, i, mesh);
//
//            glBindVertexArray(0);
//        }
    }

    Mesh() {
    }

    virtual ~Mesh() {
//        glDeleteVertexArrays(vaos.size(), vaos.data());
    }

    void draw(size_t frame = 0, const vector<mat4>& models = { }) {

        frames.at(frame).vao->bind();

        glDrawElements(frames.at(frame).drawMode, frames.at(frame).vio->getElementsCount(), GL_UNSIGNED_SHORT, nullptr);

        frames.at(frame).vao->unbind();
    }

//    void bindBuffer(Program *shader, const MeshIn &mesh, size_t attribute, size_t frame) {
//
//        auto it = attributes.at(attribute).vbos.begin();
//        while(!it->inRange(frame))
//            ++it;
//
//        glBindBuffer(GL_ARRAY_BUFFER, it->data);
//    }
//
//    void bindIndexBuffer(Program *shader, size_t frame, const MeshIn &mesh) {
//        auto it = ibos.begin();
//        while (!it->inRange(frame))
//            it++;
//
//        if (it->data) {
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->data);
//        } else {
//            glGenBuffers(1, &it->data);
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->data);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t), nullptr, GL_STATIC_DRAW);
//        }
//    }

    size_t getFrameCount() const {
        return frames.size();
    }

protected:
    vector<Frame> frames;


    /*
    vector<Attribute>                 attributesData;
    vector<Uniform>                   uniformsData;

    vector<Range<vector<uint16_t>>>   indeces;
    vector<Range<GLenum>>             drawModes;
    */
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

