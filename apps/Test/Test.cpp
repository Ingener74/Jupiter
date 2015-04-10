/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <climits>

#include <GL/glew.h>
#ifdef  _WIN32
    #include <GL/wglew.h>
#else
    #include <GL/glxew.h>
#endif


//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shaders.h"
#include "Tools.h"

using namespace std;
using namespace glm;

void init();
void deinit();
void display(void);
void reshape(int w, int h);
void mouse(int button, int action, int x, int y);
void mouseMove(int x, int y);
void key ( unsigned char key, int x, int y );
void specKey ( int key, int x, int y );
void timer(int time);

void shaderInfo(GLuint shader);

template<typename T, typename ... Args>
unique_ptr<T> make_unique_(Args ... args) {
    return unique_ptr<T>(new T(args...));
}

/*
}

// vertex shader

uniform   mat4  projection, model;
uniform   vec4  lightPosition, lightColor;

attribute vec4  vertex;
attribute vec4  color;

varying   vec4  vcolor;

void main(){
    gl_Position = projection * model * vertex;
    vcolor = color;
}

// fragment shader

uniform sampler2D tex;
uniform sampler2D bump;

varying vec4 texCoords;
varying vec4 bumpCoords;

varying vec4 vcolor;

void main(){

    vec4 rgb = sampler2D(tex, texCoords);
    vec4 norm = sampler2D(bump, bumpCoords);

    gl_FragColor = vcolor;
}

*/

string coloredSpriteVertex = R"(

uniform   mat4 projection, view, model;

attribute vec4 vertex;
attribute vec4 color;

varying vec4 vcolor;

void main(){
    gl_Position = projection * view * model * vertex;
    vcolor = color;
}

)", coloredSpriteFragment = R"(

varying vec4 vcolor;

void main(){
    gl_FragColor = vcolor;
}

)", texturedSpriteVertex = R"(

uniform   mat4 projection, view, model;

attribute vec4 vertex;
attribute vec2 texcoord;

varying vec2 vtexcoord;

void main(){
    gl_Position = projection * view * model * vertex;
    vtexcoord = texcoord;
}

)", texturedSpriteFragment = R"(

varying vec2 vtexcoord;

uniform sampler2D texture;

void main(){
    gl_FragColor = texture2D(texture, vtexcoord);
}

)", testSpriteVertex = R"(

uniform   mat4 projection, view, model;

attribute vec4 vertex;
attribute vec2 texcoord;

varying vec2 vtexcoord;

void main(){
    gl_Position = projection * view * model * vertex;
    vtexcoord = texcoord;
}

)", testSpriteFragment = R"(

varying vec2 vtexcoord;

uniform sampler2D texture;

void main(){
    gl_FragColor = texture2D(texture, vtexcoord);
}

)";

/*
 *   0                       1
 * -x  y                    x y
 *   X                       X
 *
 *   2                       3
 * -x -y                    x -y
 *   X                       X
 */

struct VertexPositionColor{
    vec3 pos, rgb;
};

struct VertexPositionTexCoord {
    vec3 pos;
    vec2 tc;
};

vector<VertexPositionColor> flour = {
    {{-35.f, 9.f, 0.f}, {.5f, .4f, .1f}},
    {{ 35.f, 9.f, 0.f}, {.5f, .4f, .1f}},
    {{-35.f,-9.f, 0.f}, {.5f, .4f, .1f}},
    {{ 35.f,-9.f, 0.f}, {.5f, .4f, .1f}},
}, box = {
    {{-3.f, 3.f, 0.f},   {.3f, .6f, .1f}},
    {{ 3.f, 3.f, 0.f},   {.3f, .6f, .1f}},
    {{-3.f,-3.f, 0.f},   {.3f, .6f, .1f}},
    {{ 3.f,-3.f, 0.f},   {.3f, .6f, .1f}},
}, boxHead = {
    {{-3.f,  0.f, 0.f},   {.3f, .6f, .8f}},
    {{ 3.f,  0.f, 0.f},   {.3f, .6f, .4f}},
    {{ 0.f, 15.f, 0.f},   {1.f, 1.f, 1.f}},
}, bg = {
    {{-100.f, 40.f, 0.f}, {.7f, .7f, .7f}},
    {{ 100.f, 40.f, 0.f}, {.7f, .7f, .7f}},
    {{-100.f,-40.f, 0.f}, {.7f, .7f, .7f}},
    {{ 100.f,-40.f, 0.f}, {.7f, .7f, .7f}},
};

vector<VertexPositionTexCoord> tBox = {
    {{-10.f, 10.f, 0.f},   {0.f, 0.f}},
    {{ 10.f, 10.f, 0.f},   {1.f, 0.f}},
    {{-10.f,-10.f, 0.f},   {0.f, 1.f}},
    {{ 10.f,-10.f, 0.f},   {1.f, 1.f}},
};

vector<uint16_t> flourInd = {
    0, 2, 1,   3
//    0, 2, 1,   3, 1, 2,
}, boxInd = {
    0, 2, 1,   3, 1, 2,
}, boxHeadInd = {
    0, 2, 1,
}, bgInd = {
    0, 2, 1,   3, 1, 2,
}, tBoxInd = {
    0, 2, 1,   3, 1, 2,
};

//
vector<vec3> shipVerteces = {
    {-5.f, 5.f, 0.f},
    { 5.f, 5.f, 0.f},
    {-5.f,-5.f, 0.f},
    { 5.f,-5.f, 0.f},
};
vector<vec2> shipTexCoords = {
    {0.f, 0.f},
    {1.f, 0.f},
    {0.f, 1.f},
    {1.f, 1.f},
};
vector<uint16_t> shipIndices = {
    0, 2, 1, 3
};

float w = 400.f, h = 240.f, m = .5f;
float width = w * m, height = h * m;

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
    Uniform(GLint uniform = 0, string uniformName = {}) :
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
        auto it = find_if(uniforms.begin(), uniforms.end(), [&](const Uniform& i) {return i.uniformName == uniformName;});
        if (it == uniforms.end())
            throw runtime_error("no uniform");
        glUniformMatrix4fv(it->uniform, 1, GL_FALSE, &matrix[0][0]);
    }

    friend ostream& operator<<(ostream& out, const Program& r){
        return out << "program id " << r.program << " attributes [ " << [&](){
            stringstream s;
            for(auto i: r.attributes)
                s << i << "; ";
            return s.str();
        }() << "], uniforms [ " << [&](){
            stringstream s;
            for(auto i: r.uniforms)
                s << i << "; ";
            return s.str();
        }() << "]";
    }

protected:
};

class ColoredShader {
public:
    GLuint shader = 0, aVertex = 0, aColor = 0, uProjection = 0, uView = 0, uModel = 0;
};
ColoredShader cs;

class TexturedShader {
public:
    GLuint shader = 0, aVertex = 0, aTexCoord = 0, uProjection = 0, uView = 0, uModel = 0, uTexture = 0;
};
TexturedShader ts;

class ColoredSprite{
public:
    ColoredSprite(){
    }
    ColoredSprite(const ColoredShader& shader, const vector<VertexPositionColor>& vertexes,
        const vector<uint16_t>& indexes, GLenum drawMode) {

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(VertexPositionColor), &vertexes.front().pos.x, GL_STATIC_DRAW);

        glEnableVertexAttribArray(shader.aVertex);
        glVertexAttribPointer(shader.aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*) offsetof(VertexPositionColor, pos));

        glEnableVertexAttribArray(shader.aColor);
        glVertexAttribPointer(shader.aColor,  3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*) offsetof(VertexPositionColor, rgb));

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint16_t), indexes.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        ColoredSprite::indexes = indexes.size();
        ColoredSprite::drawMode = drawMode;
    }

    virtual ~ColoredSprite() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void draw(const vector<mat4>& parentsModels = { }) {

        if (parentsModels.empty()) {
            glUniformMatrix4fv(cs.uModel, 1, GL_FALSE, &model[0][0]);
        } else {
            auto m = accumulate(parentsModels.begin() + 1, parentsModels.end(), parentsModels.front(), multiplies<mat4>()) * model;
            glUniformMatrix4fv(cs.uModel, 1, GL_FALSE, &m[0][0]);
        }

        glBindVertexArray(VAO);
        glDrawElements(drawMode, indexes, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

    GLuint VBO = 0, IBO = 0, VAO = 0;
    size_t indexes = 0;
    mat4   model;
    GLenum drawMode;
};

class TexturedSprite: public ColoredSprite{
public:
    TexturedSprite(const TexturedShader& shader, const vector<VertexPositionTexCoord>& vertexes, const vector<uint16_t>& indexes, GLenum drawMode, const Texture& texture){

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(VertexPositionTexCoord), &vertexes.front().pos.x, GL_STATIC_DRAW);

        glEnableVertexAttribArray(shader.aVertex);
        glVertexAttribPointer(shader.aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexCoord), (void*)offsetof(VertexPositionTexCoord, pos));

        glEnableVertexAttribArray(shader.aTexCoord);
        glVertexAttribPointer(shader.aTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexCoord), (void*)offsetof(VertexPositionTexCoord, tc));

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint16_t), indexes.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        TexturedSprite::indexes = indexes.size();
        TexturedSprite::drawMode = drawMode;
        TexturedSprite::texture = texture;
    }

    TexturedSprite(const TexturedShader& shader, const vector<vec3>& verteces, const vector<vec2>& texcoords, const vector<uint16_t>& indexes, GLenum drawMode, const Texture& texture){

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verteces.size() * sizeof(vec3), &verteces.front().x, GL_STATIC_DRAW);

        glEnableVertexAttribArray(shader.aVertex);
        glVertexAttribPointer(shader.aVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, &vboTexCoords);
        glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(vec2), &texcoords.front().x, GL_STATIC_DRAW);

        glEnableVertexAttribArray(shader.aTexCoord);
        glVertexAttribPointer(shader.aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint16_t), indexes.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        TexturedSprite::indexes = indexes.size();
        TexturedSprite::drawMode = drawMode;
        TexturedSprite::texture = texture;
    }

    /*
     *
     */

    virtual ~TexturedSprite(){
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
        glDeleteVertexArrays(1, &VAO);
        glDeleteTextures(1, &texture.textureId);
    }

    void draw(const vector<mat4>& parentsModels = { }) {

        if (parentsModels.empty()) {
            glUniformMatrix4fv(ts.uModel, 1, GL_FALSE, &model[0][0]);
        } else {
            auto m = accumulate(parentsModels.begin() + 1, parentsModels.end(), parentsModels.front(),
                multiplies<mat4>()) * model;
            glUniformMatrix4fv(ts.uModel, 1, GL_FALSE, &m[0][0]);
        }

        GLint textureUnit = 0;
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture.textureId);
        glUniform1i(ts.uTexture, textureUnit);

        glBindVertexArray(VAO);
        glDrawElements(drawMode, indexes, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

    vector<GLuint> vbos;
    GLuint vboTexCoords = 0;
    Texture texture;
};




/*
 * кадры могут делить координаты, текстурный координаты, текстуры, индексы и пр.
 * один кадр хранит информаци по текущему состоянию меша, т.е. какой использовать,
 *      буфер координат,
 *      буфер текстурных координат,
 *      буфер цветов,
 *      буфер нормалей,
 *      текстуру
 *      и т. д.
 *
 *
 *
 */

/*

{
    {   // Первый кадр
        {   // Аттрибуты шейдера
            {
                pos,
                3,
                {   // Координаты
                    0.f, 0.f, 0.f,
                    0.f, 0.f, 0.f,
                    0.f, 0.f, 0.f,
                    0.f, 0.f, 0.f,
                }
            },
            {
                texcoord,
                2,
                {   // Текстурный координаты
                    0.f, 0.f,
                    0.f, 0.f,
                    0.f, 0.f,
                    0.f, 0.f,
                }
            }
        },
        {   // Индексы
            1, 2, 3, 4,
        },
        {   // Текстура
            "image.png",
        }
    },

    {   // Второй кадр
    }
}

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
struct FrameRange {
    int32_t start, end;
    T data;
};

struct MeshData{

    struct Attribute {
        string attribute;
        vector<FrameRange<vector<float>>> data;
    };
    struct Texture{
        GLuint textureId;
        GLuint unit;
    };
    struct Uniform {
        string                           uniform;
        vector<FrameRange<Texture>>      textures;
    };

    int                                  frames;
    vector<Attribute>                    attributesData;

    vector<Uniform>                      uniformsData;

    vector<FrameRange<vector<uint16_t>>> indeces;
    vector<FrameRange<GLenum>>           drawModes;
};


MeshData boxMeshData{
    3,
    {
        {
            "pos",
            {
                {0, 3, {0.f, 0.f, 0.f,  0.f, 0.f, 0.f,  0.f, 0.f, 0.f,  0.f, 0.f, 0.f,  }}
            }
        },
        {
            "texcoord",
            {
                {
                    0, 1, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  }
                },
                {
                    1, 2, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  }
                },
                {
                    2, 3, {0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  0.f, 0.f,  }
                },
            }
        }
    },
    {
        {
            "texture",
            {
                {
                    0, 3, {3, 0}
                }
            }
        }, {
            "bump",
            {
                {
                    0, 3, {5, 0}
                }
            }
        }
    },
    {
        {
            0, 3, {0, 1, 2, 3}
        }
    },
    {
        {
            0, 3, GL_TRIANGLE_STRIP
        }
    }
};

class Mesh {
public:
    /*
    Mesh(const Program& shaderProgram, const vector<VertexAttributeData>& mesh){
        vbos.resize(mesh.size());

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(mesh.size(), vbos.data());

        for(size_t i = 0; i < mesh.size(); ++i){
            glBindBuffer(GL_ARRAY_BUFFER, vbos.at(i));
            glBufferData(GL_ARRAY_BUFFER, mesh.at(i).data.size() * mesh.at(i).size * sizeof(float), mesh.at(i).data.data(), GL_STATIC_DRAW);

            auto attrib = shaderProgram.getAttribute(mesh.at(i).attributeName).attribute;
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib, mesh.at(i).size, GL_FLOAT, GL_FALSE, 0, 0);
        }

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces.size() * sizeof(uint16_t), indeces.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        TexturedSprite::indexes = indeces.size();
        TexturedSprite::drawMode = drawMode;
    }
    */
    Mesh() {
    }

    virtual ~Mesh() {
    }

    void draw(const std::vector<mat4>& models) {
    }
};

unique_ptr<ColoredSprite> boxSprite, flourSprite, bgSprite, boxHeadSprite;
unique_ptr<TexturedSprite> tBoxSprite, ship;

unique_ptr<Program> coloredSh, texturedSh;

unique_ptr<Mesh>
    root,
        bgMesh,
        groundMesh,
        boxMesh;

mat4 proj, view;

string boxImage, shipImage;

int main(int argc, char **argv) {
    try {
        if(argc < 3)
            throw invalid_argument("usage: ./Test <path-to-image-file>/box.png <path-to-image-file/ship.png");

        boxImage  = argv[1];
        shipImage = argv[2];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);

        // Для OpenGL 3.3
        glutInitContextVersion(3, 3);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
        glutInitContextProfile(GLUT_CORE_PROFILE);

        glutCreateWindow("Test");

        glewExperimental = GL_TRUE;
        auto glewInitError = glewInit();
        if (glewInitError != GLEW_OK)
            throw runtime_error("glew init error " + string(reinterpret_cast<const char*>(glewGetErrorString(glewInitError))));

        {
            cout << "OpenGL vendor:                     " << glGetString(GL_VENDOR) << endl;
            cout << "OpenGL renderer:                   " << glGetString(GL_RENDERER) << endl;
            cout << "OpenGL version:                    " << glGetString(GL_VERSION) << endl;
            cout << "OpenGL shading language version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
//            stringstream s;
//            s << glGetString(GL_EXTENSIONS);
//            string ext;
//            while (s >> ext)
//                cout << ext << endl;
        }

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);
        glutKeyboardFunc(key);
        glutSpecialFunc(specKey);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);

        reshape(width, height);
        init();

        glutTimerFunc(0, timer, 0);
        glutMainLoop();

        deinit();

        return EXIT_SUCCESS;
    } catch (std::exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}

void init(){

    coloredSh = make_unique_<Program>(coloredSpriteVertex, coloredSpriteFragment);
    cout << *coloredSh << endl;

    texturedSh = make_unique_<Program>(texturedSpriteVertex, texturedSpriteFragment);
    cout << *texturedSh << endl;

    texturedSh->setUniformMatrix4x4("projection", proj);
    texturedSh->setUniformMatrix4x4("view", view);

    {
        cs.shader = createProgram(coloredSpriteVertex, coloredSpriteFragment);

        cs.uProjection = glGetUniformLocation(cs.shader, "projection");
        cs.uView       = glGetUniformLocation(cs.shader, "view");
        cs.uModel      = glGetUniformLocation(cs.shader, "model");

        cs.aVertex     = glGetAttribLocation(cs.shader, "vertex");
        cs.aColor      = glGetAttribLocation(cs.shader, "color");

        glUseProgram(cs.shader);
        glUniformMatrix4fv(cs.uProjection, 1, GL_FALSE, &proj[0][0]);
        glUniformMatrix4fv(cs.uView, 1, GL_FALSE, &view[0][0]);
    }
    {
        ts.shader = createProgram(texturedSpriteVertex, texturedSpriteFragment);

        ts.uProjection = glGetUniformLocation(ts.shader, "projection");
        ts.uView       = glGetUniformLocation(ts.shader, "view");
        ts.uModel      = glGetUniformLocation(ts.shader, "model");

        ts.uTexture    = glGetUniformLocation(ts.shader, "texture");

        ts.aVertex     = glGetAttribLocation(ts.shader, "vertex");
        ts.aTexCoord   = glGetAttribLocation(ts.shader, "texcoord");

        glUseProgram(ts.shader);
        glUniformMatrix4fv(ts.uProjection, 1, GL_FALSE, &proj[0][0]);
        glUniformMatrix4fv(ts.uView, 1, GL_FALSE, &view[0][0]);
    }

    boxSprite      = make_unique_<ColoredSprite>(cs, box,      boxInd,      GL_TRIANGLES);
    flourSprite    = make_unique_<ColoredSprite>(cs, flour,    flourInd,    GL_TRIANGLE_STRIP);
    bgSprite       = make_unique_<ColoredSprite>(cs, bg,       bgInd,       GL_TRIANGLES);
    boxHeadSprite  = make_unique_<ColoredSprite>(cs, boxHead,  boxHeadInd,  GL_TRIANGLES);

    if (boxImage.empty())
        throw runtime_error("image file name is empty");

    tBoxSprite     = make_unique_<TexturedSprite>(ts, tBox,     tBoxInd,     GL_TRIANGLES, loadTexture(boxImage));
    ship           = make_unique_<TexturedSprite>(ts, shipVerteces, shipTexCoords, shipIndices, GL_TRIANGLE_STRIP, loadTexture(shipImage));

    boxSprite->model        = glm::translate(boxSprite->model,     vec3(0.f,  30.f,  0.f));
    boxHeadSprite->model    = glm::translate(boxHeadSprite->model, vec3(0.f,  3.0f,  0.f));
    flourSprite->model      = glm::translate(flourSprite->model,   vec3(0.f, -40.f,  0.f));
    bgSprite->model         = glm::translate(bgSprite->model,      vec3(0.f,   0.f, -1.f));
    tBoxSprite->model       = glm::translate(tBoxSprite->model,    vec3(0.f, -13.f,  4.f));

    ship->model             = glm::translate(ship->model,          vec3(0.f,  -20.f,  5.f));
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
//    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    {
        glUseProgram(cs.shader);

        boxSprite->model = glm::rotate(boxSprite->model, .03f, vec3(0.f, 0.f, 1.f));

        bgSprite->draw();
        flourSprite->draw();
        boxSprite->draw();
        boxHeadSprite->draw( { boxSprite->model });
    }

    {
        glUseProgram(ts.shader);

        tBoxSprite->draw( { boxSprite->model });
        ship->draw();
    }

    glFlush();
    glutSwapBuffers();
}

void timer(int time) {

    glutPostRedisplay();

    int delay = 1000 / 30;
    glutTimerFunc(delay, timer, 0);
}

void mouse(int button, int action, int x, int y) {
}

void mouseMove(int x, int y) {
}

void key(unsigned char k, int x, int y) {
    if (k == 27)
        glutLeaveMainLoop();
}

void specKey ( int key, int x, int y ){
}

void deinit(){
    glDeleteProgram(cs.shader);
    glDeleteProgram(ts.shader);

    boxSprite.reset();
    bgSprite.reset();
    flourSprite.reset();
    boxHeadSprite.reset();
    tBoxSprite.reset();
}

void shaderInfo(GLuint shader){

    static map<int, string> types = {
        {GL_FLOAT        , "GL_FLOAT       "},
        {GL_FLOAT_VEC2   , "GL_FLOAT_VEC2  "},
        {GL_FLOAT_VEC3   , "GL_FLOAT_VEC3  "},
        {GL_FLOAT_VEC4   , "GL_FLOAT_VEC4  "},
        {GL_FLOAT_MAT2   , "GL_FLOAT_MAT2  "},
        {GL_FLOAT_MAT3   , "GL_FLOAT_MAT3  "},
        {GL_FLOAT_MAT4   , "GL_FLOAT_MAT4  "},
        {GL_FLOAT_MAT2x3 , "GL_FLOAT_MAT2x3"},
        {GL_FLOAT_MAT2x4 , "GL_FLOAT_MAT2x4"},
        {GL_FLOAT_MAT3x2 , "GL_FLOAT_MAT3x2"},
        {GL_FLOAT_MAT3x4 , "GL_FLOAT_MAT3x4"},
        {GL_FLOAT_MAT4x2 , "GL_FLOAT_MAT4x2"},
        {GL_FLOAT_MAT4x3 , "GL_FLOAT_MAT4x3"},
        {GL_INT          , "GL_INT         "},
        {GL_INT_VEC2     , "GL_INT_VEC2    "},
        {GL_INT_VEC3     , "GL_INT_VEC3    "},
        {GL_INT_VEC4     , "GL_INT_VEC4    "},
        {GL_BOOL         , "GL_BOOL        "},
        {GL_BOOL_VEC2    , "GL_BOOL_VEC2   "},
        {GL_BOOL_VEC3    , "GL_BOOL_VEC3   "},
        {GL_BOOL_VEC4    , "GL_BOOL_VEC4   "},
        {GL_SAMPLER_2D   , "GL_SAMPLER_2D  "},
        {GL_SAMPLER_CUBE , "GL_SAMPLER_CUBE"},
    };

    GLint activeAttributes = 0;
    glGetProgramiv(shader, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
    cout << "activeAttributes " << activeAttributes << endl;

    for (GLint i = 0; i < activeAttributes; ++i) {

        const GLsizei bufferSize = 100;

        GLsizei lenght = 0;
        GLint size = 0;
        GLenum type = 0;
        GLchar name[bufferSize];

        glGetActiveAttrib(shader, i, bufferSize, &lenght, &size, &type, name);

        cout << lenght << " " << size << " " << types[type] << " " << name << endl;
    }

    GLint activeUniforms = 0;
    glGetProgramiv(shader, GL_ACTIVE_UNIFORMS, &activeUniforms);
    cout << "activeUniforms " << activeUniforms << endl;

    for (GLint i = 0; i < activeUniforms; ++i) {
        const GLsizei bufferSize = 100;

        GLsizei lenght = 0;
        GLint size = 0;
        GLenum type = 0;
        GLchar name[bufferSize];

        glGetActiveUniform(shader, i, bufferSize, &lenght, &size, &type, name);

        cout << lenght << " " << size << " " << types[type] << " " << name << endl;
    }
}
