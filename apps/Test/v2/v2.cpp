/*
 * v2.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

#include "main.h"

using namespace std;
using namespace glm;


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

class Attribute {
public:
    Attribute(GLint attribute = 0, string attributeName = { }) :
        attribute(attribute), attributeName(attributeName) {
    }

    GLint attribute = 0;
    string attributeName;

    friend ostream& operator<<(ostream& out, const Attribute& r) {
        return out << r.attributeName << ": " << r.attribute;
    }
};

class Uniform {
public:
    Uniform(GLint uniform = 0, string uniformName = { }) :
        uniform(uniform), uniformName(uniformName) {
    }
    GLint uniform = 0;
    string uniformName;

    friend ostream& operator<<(ostream& out, const Uniform& r) {
        return out << r.uniformName << ": " << r.uniform;
    }
};

class Program {
public:
    Program(const string& vertesShader, const std::string& fragmentShader) {
        program = createProgram(vertesShader, fragmentShader);

        GLint activeAttributes = 0;
        glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);

        for (GLint i = 0; i < activeAttributes; ++i) {

            const GLsizei bufferSize = 100;

            GLsizei lenght = 0;
            GLint size = 0;
            GLenum type = 0;
            GLchar name[bufferSize];

            glGetActiveAttrib(program, i, bufferSize, &lenght, &size, &type, name);

            attributes.emplace_back(glGetAttribLocation(program, name), name);
        }

        GLint activeUniforms = 0;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);

        for (GLint i = 0; i < activeUniforms; ++i) {
            const GLsizei bufferSize = 100;

            GLsizei lenght = 0;
            GLint size = 0;
            GLenum type = 0;
            GLchar name[bufferSize];

            glGetActiveUniform(program, i, bufferSize, &lenght, &size, &type, name);

            uniforms.emplace_back(glGetUniformLocation(program, name), name);
        }
    }
    virtual ~Program() {
        glDeleteProgram(program);
    }

    GLuint program = 0;
    vector<Attribute> attributes;
    vector<Uniform> uniforms;

    const Attribute& getAttribute(const string& attributeName) const {
        auto it = find_if(attributes.begin(), attributes.end(),
            [&](const Attribute& i) {return i.attributeName == attributeName;});
        if (it == attributes.end())
            throw runtime_error("no attribute with name " + attributeName);
        return *it;
    }

    void setUniformMatrix4x4(const string& uniformName, const mat4& matrix) {
        auto it = find_if(uniforms.begin(), uniforms.end(),
            [&](const Uniform& i) {return i.uniformName == uniformName;});
        if (it == uniforms.end())
            throw runtime_error("no uniform");
        glUniformMatrix4fv(it->uniform, 1, GL_FALSE, &matrix[0][0]);
    }

    friend ostream& operator<<(ostream& out, const Program& r) {
        return out << "program id " << r.program << " attributes [ " << [&]() {
            stringstream s;
            for(auto i: r.attributes)
            s << i << "; ";
            return s.str();
        }() << "], uniforms [ " << [&]() {
            stringstream s;
            for(auto i: r.uniforms)
            s << i << "; ";
            return s.str();
        }() << "]";
    }

protected:
};

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
    int32_t start, end;
    T data;

    bool inRange(int32_t i) const {
        return i >= start && i < end;
    }
};

struct MeshData{

    struct Attribute {
        string attribute;
        vector<Range<vector<float>>> data;
    };
    struct Texture{
        GLuint textureId;
        GLuint unit;
    };
    struct Uniform {
        string                           uniform;
        vector<Range<Texture>>      textures;
    };

    int                                  frames;

    vector<Attribute>                    attributesData;
    vector<Uniform>                      uniformsData;

    vector<Range<vector<uint16_t>>> indeces;
    vector<Range<GLenum>>           drawModes;
};

/*
MeshData boxMeshData{
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

class Mesh {
public:

    struct MeshAttrib {
        vector<Range<GLuint>> vbo;
    };

    Mesh(Program* shaderProgram, const MeshData& mesh){

        vaos = vector<GLuint>(mesh.frames);

        glGenVertexArrays(vaos.size(), vaos.data());

        for(size_t i = 0; i < mesh.frames; ++i){
            glBindVertexArray(vaos.at(i));

//            glGenBuffers(mesh.size(), vbos.data());
//
//            for(size_t i = 0; i < mesh.size(); ++i){
//                glBindBuffer(GL_ARRAY_BUFFER, vbos.at(i));
//                glBufferData(GL_ARRAY_BUFFER, mesh.at(i).data.size() * mesh.at(i).size * sizeof(float), mesh.at(i).data.data(), GL_STATIC_DRAW);
//
//                auto attrib = shaderProgram.getAttribute(mesh.at(i).attributeName).attribute;
//                glEnableVertexAttribArray(attrib);
//                glVertexAttribPointer(attrib, mesh.at(i).size, GL_FLOAT, GL_FALSE, 0, 0);
//            }
//
//            glGenBuffers(1, &IBO);
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces.size() * sizeof(uint16_t), indeces.data(), GL_STATIC_DRAW);

            glBindVertexArray(0);
        }
    }

    Mesh() {
    }

    virtual ~Mesh() {
        glDeleteVertexArrays(vaos.size(), vaos.data());
    }

    void draw(size_t frame = 0, const std::vector<mat4>& models = { }) {

        glBindVertexArray(vaos.at(frame));

        glDrawElements(drawModes.at(frame), elementsCounts.at(frame), GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0);
    }

    size_t getFrameCount() const {
        return vaos.size();
    }

protected:
    vector<GLuint> vaos;
    vector<GLsizei> elementsCounts;
    vector<GLenum>  drawModes;
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

