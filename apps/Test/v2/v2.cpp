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

string vertex_texture = R"(

#version 330

uniform mat4 projection, view, model;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoord;

out vec2 texcoord_;

void main(){
    gl_Position = projection * view * model * position;
    texcoord_ = texcoord;
}

)", fragment_texture = R"(

#version 330

uniform sampler2D texture;

in vec2 texcoord_;

out vec4 fragColor;

void main(){
    fragColor = texture2D(texture, texcoord_);
}

)";

struct AttributeRaw {
    string name;
    int size;
    vector<float> data;
};

struct AttributeGL {
    AttributeGL(Program* program, const AttributeRaw& attrib) {

        if (attrib.data.empty())
            throw invalid_argument("attribute: data empty");

        name = program->getAttribute(attrib.name).attribute;
        size = attrib.size;

        glGenBuffers(1, &data);
        glBindBuffer(GL_ARRAY_BUFFER, data);
        glBufferData(GL_ARRAY_BUFFER, attrib.data.size() * sizeof(float), attrib.data.data(), GL_STATIC_DRAW);
    }
    virtual ~AttributeGL() {
        glDeleteBuffers(1, &data);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, data);
        glEnableVertexAttribArray(name);
        glVertexAttribPointer(name, size, GL_FLOAT, GL_FALSE, 0, 0);
    }

    GLint name;
    GLint size;
    GLuint data;
};

class TextureRaw {
public:
    string     file;
    string     uniform;
    uint16_t   unit;
};

class TextureGL {
public:
    TextureGL(Program* program, const TextureRaw& texture) {

        uniform = program->getUniform(texture.uniform).uniform;

        Texture tex = loadTexture(texture.file);

        id = tex.textureId;
        unit = texture.unit;
    }
    ~TextureGL(){
        glDeleteTextures(1, &id);
    }

    void bind() const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, id);
        glUniform1i(uniform, unit);
    }

    GLuint     id      = 0;
    GLint      uniform = 0;
    GLuint     unit    = 0;
};

class ElementsRaw{
public:
    vector<uint16_t> elements;
};

class ElementsGL{
public:
    ElementsGL(const ElementsRaw& elements){
        if(elements.elements.empty())
            throw invalid_argument("elements empty");

        glGenBuffers(1, &data);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.elements.size() * sizeof(uint16_t), elements.elements.data(), GL_STATIC_DRAW);

        elementsCount = elements.elements.size();
    }

    ElementsGL() { }

    virtual ~ElementsGL() {
        glDeleteBuffers(1, &data);
    }

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data);
    }

    GLuint data = 0;
    GLuint elementsCount = 0;
};

class FrameRaw {
public:
    vector<AttributeRaw> attributesData;
    vector<TextureRaw>   textureData;
    ElementsRaw          elements;
    GLenum               drawMode;
};

class FrameGL {
public:
    FrameGL(Program* program, const FrameRaw& frame) {
        for (auto const& i : frame.attributesData) {
            attributesData.push_back( { program, i });
        }
        for (auto const& i : frame.textureData) {
            textureData.push_back( { program, i });
        }
        elements = ElementsGL{frame.elements};
        drawMode = frame.drawMode;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        for(auto const& i: attributesData)
            i.bind();

        elements.bind();

        glBindVertexArray(0);
    }

    void bind() const {
        for (auto const& i : textureData)
            i.bind();
        glBindVertexArray(vao);
    }

    GLuint              vao;
    vector<AttributeGL> attributesData;
    vector<TextureGL>   textureData;
    ElementsGL          elements;
    GLenum              drawMode;
};

class Mesh {
public:
    Mesh(const vector<FrameRaw>& frames) :
        frames(frames) {
    }
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

class Node {
public:
    Node(Program* program, mat4 const& model, Mesh const& mesh) {
        _program = program;
        _mesh    = MeshGL { program, mesh };
        _model   = model;
    }
    virtual ~Node() {
    }

    virtual void draw(vector<mat4> const& models = { }) {
        _program->use();
        _program->setUniformMatrix4x4("model", _model);

        auto const& frame = _mesh.frames.at(0);

        frame.bind();

        glDrawElements(frame.drawMode, frame.elements.elementsCount, GL_UNSIGNED_SHORT, 0);
    }

    Program* _program = nullptr;
    mat4     _model;
    MeshGL   _mesh;
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
    texturedProgram = make_unique_<Program>(vertex_texture, fragment_texture);
    cout << "shader: " << *texturedProgram << endl;

    texturedProgram->use();
    texturedProgram->setUniformMatrix4x4("projection", proj);
    texturedProgram->setUniformMatrix4x4("view", view);

    Mesh pressMeMesh{
        // Frames
        {
            // Frame 0
            {
                // Attributes
                {
                    // Attrib 0
                    {
                        "position",
                        3,
                        {
                            -4.f,  4.f, 0.f,
                             4.f,  4.f, 0.f,
                            -4.f, -4.f, 0.f,
                             4.f, -4.f, 0.f
                        }
                    },
                    {
                        "texcoord",
                        2,
                        {
                            -1.f,  1.f,
                             1.f,  1.f,
                            -1.f, -1.f,
                             1.f, -1.f
                        }
                    }
                },
                // Uniforms
                {
                    // Texture 0
                    {
                        getBase() + "/Resources/button-1/pressme.png",
                        "texture",
                        0
                    }
                },
                // Elements
                {
                    {0, 2, 1, 3}
                },
                // Draw mode
                GL_TRIANGLE_STRIP
            }
        }
    };

    pressMe = make_unique_<Node>(texturedProgram.get(), mat4{}, pressMeMesh);
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    texturedProgram->use();
    texturedProgram->setUniformMatrix4x4("projection", proj);
    texturedProgram->setUniformMatrix4x4("view", view);

    pressMe->draw();

    glFlush();
    glutSwapBuffers();
}

void deinit() {
}

