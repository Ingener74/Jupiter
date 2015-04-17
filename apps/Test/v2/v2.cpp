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

string vertex_color = R"(

#version 330

uniform mat4 projection, view, model;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoord;

out vec2 texcoord_;

void main(){
    gl_Position = projection * view * model * position;
    texcoord_ = texcoord;
}

)", fragment_color = R"(

#version 330

uniform sampler2D texture;

in vec2 texcoord_;

out vec4 fragColor;

void main(){
    fragColor = texture2D(texture, texcoord_);
}

)";

struct AttributeRaw{
    string        name;
    vector<float> data;
};

struct AttributeGL{

    AttributeGL(Program* program, const AttributeRaw& attrib){
        name = program->getAttribute(attrib.name).attribute;

        glGenBuffers(1, &data);
        glBindBuffer(GL_ARRAY_BUFFER, data);
        glBufferData(GL_ARRAY_BUFFER, attrib.data.size() * sizeof(float), attrib.data.data(), GL_STATIC_DRAW);
    }

    GLint  name;
    GLuint data;
};

class FrameRaw{
public:
    vector<AttributeRaw> attributesData;
};

class FrameGL{
public:
    FrameGL(Program* program, const FrameRaw& frame) {
        for (auto const& i : frame.attributesData) {
            attributesData.push_back( { program, i });
        }
    }

    vector<AttributeGL> attributesData;
};

class Mesh{
public:
    Mesh(const vector<FrameRaw>& frames): frames(frames){}

    vector<FrameRaw> frames;
};

class MeshGL {
public:
    MeshGL() {
    }
    MeshGL(Program* program, const Mesh& mesh) {
        for (auto const& i : mesh.frames) {
            frames.push_back( { program, i });
        }
    }

    vector<FrameGL> frames;
};

class Node{
public:
    Node(Program* program, const mat4& model, const Mesh& mesh){

        Node::mesh = MeshGL{program, mesh};

    }
    virtual ~Node(){}

    virtual void draw(const vector<mat4>& models = {}){}

    Program* program = nullptr;
    mat4     model;
    MeshGL   mesh;
};

unique_ptr<Program>   texturedProgram;
unique_ptr<Node>      pressMe;

mat4 proj, view;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void init() {
    texturedProgram = make_unique_<Program>(vertex_color, fragment_color);
    cout << "shader: " << *texturedProgram << endl;

    texturedProgram->setUniformMatrix4x4("projection", proj);
    texturedProgram->setUniformMatrix4x4("view", view);

    Mesh pressMeMesh{
        { // Frames
            { // Frame 0
                { // Attributes
                    { // Attrib 0
                        "position",
                        {0.f, 0.f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f, 0.f}
                    },
                    {
                        "texcoord",
                        {0.f, 0.f,   0.f, 0.f,   0.f, 0.f}
                    }
                }
            }/*,
            {

            }*/
        }
    };

    pressMe = make_unique_<Node>(texturedProgram.get(), mat4{}, pressMeMesh);

    cout << "mesh" << endl;
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    pressMe->draw();

    glFlush();
    glutSwapBuffers();
}

void deinit() {
}

