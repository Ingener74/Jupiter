/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <numeric>
#include <array>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstddef>

#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lodepng.h"

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
void timer(int time);

/*

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
    vec3 pos, tc;
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

vector<ushort> flourInd = {
    0, 2, 1,   3, 1, 2,
}, boxInd = {
    0, 2, 1,   3, 1, 2,
}, boxHeadInd = {
    0, 2, 1,
}, bgInd = {
    0, 2, 1,   3, 1, 2,
};

float w = 400.f, h = 240.f, m = 1.f;
float width = w * m, height = h * m;

class ColoredShader {
public:
    GLuint shader = 0, aVertex = 0, aColor = 0, uProjection = 0, uView = 0, uModel = 0;
};
ColoredShader cs;

class TexturedShader{
public:
    GLuint shader = 0, aVertex = 0, aTexCoord = 0, uProjection = 0, uView = 0, uModel = 0;
};
TexturedShader ts;

enum Objects{
    Flour,
    Box,
    BoxHead,
    Bg,
    TBox,

    FlourInd,
    BoxInd,
    BoxHeadInd,
    BgInd,
    TBoxInd,

    End
};
GLuint VBOs[End];
size_t indexes[End];
mat4 models[End];
GLuint Textures[End];

mat4 proj, view;

string imageFileName;

int main(int argc, char **argv) {
    try {
        if(argc < 2)
            throw invalid_argument("usage: ./Test <path-to-image-file>/image.png");

        imageFileName = argv[1];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow("Test");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);

        if (glewInit() != GLEW_OK)
            throw runtime_error("glew init error");

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);

        init();
        reshape(width, height);

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
    {
        cs.shader = createProgram(coloredSpriteVertex, coloredSpriteFragment);

        cs.uProjection = glGetUniformLocation(cs.shader, "projection");
        cs.uView       = glGetUniformLocation(cs.shader, "view");
        cs.uModel      = glGetUniformLocation(cs.shader, "model");

        cs.aVertex     = glGetAttribLocation(cs.shader, "vertex");
        cs.aColor      = glGetAttribLocation(cs.shader, "color");
    }
    {
        ts.shader = createProgram(texturedSpriteVertex, texturedSpriteFragment);

        ts.uProjection = glGetUniformLocation(cs.shader, "projection");
        ts.uView       = glGetUniformLocation(cs.shader, "view");
        ts.uModel      = glGetUniformLocation(cs.shader, "model");

        ts.aVertex     = glGetAttribLocation(cs.shader, "vertex");
        ts.aTexCoord   = glGetAttribLocation(cs.shader, "texcoord");
    }

    glGenBuffers(End, VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Flour]);
    glBufferData(GL_ARRAY_BUFFER, flour.size() * sizeof(VertexPositionColor), &flour.front().pos.x, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Box]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(VertexPositionColor), &box.front().pos.x, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[BoxHead]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(VertexPositionColor), &boxHead.front().pos.x, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Bg]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(VertexPositionColor), &bg.front().pos.x, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[FlourInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, flourInd.size() * sizeof(ushort), flourInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxHeadInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxHeadInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BgInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), bgInd.data(), GL_STATIC_DRAW);

    if(imageFileName.empty())
        throw runtime_error("image file name is empty");

    vector<uint8_t> data;
    uint32_t w, h;
    auto error = lodepng::decode(data, w, h, imageFileName, LCT_RGBA);
    if (error)
        throw runtime_error(lodepng_error_text(error));
//    cout << w << " x " << h << " " << data.size() << endl;

    glGenTextures(End, Textures);

    glBindTexture(GL_TEXTURE_2D, Textures[TBox]);
//    glTexImage2D(GL_TEXTURE_2D, 0, )

    indexes[Flour]     = flourInd.size();
    indexes[Box]       = boxInd.size();
    indexes[BoxHead]   = boxHeadInd.size();
    indexes[Bg]        = bgInd.size();

    models[Box]        = glm::translate(models[Box],     vec3(0.f,  30.f,  0.f));
    models[BoxHead]    = glm::translate(models[BoxHead], vec3(0.f,  3.0f,  0.f));
    models[Flour]      = glm::translate(models[Flour],   vec3(0.f, -40.f,  0.f));
    models[Bg]         = glm::translate(models[Bg],      vec3(0.f,   0.f, -1.f));
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
//    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void drawObj(int obj, int objInd, const vector<mat4>& parentsModels = {}) {

    if (parentsModels.empty()) {
        glUniformMatrix4fv(cs.uModel, 1, GL_FALSE, &models[obj][0][0]);
    } else {
        auto m = accumulate(parentsModels.begin() + 1, parentsModels.end(), parentsModels.front(), multiplies<mat4>());
        m = m * models[obj];
        glUniformMatrix4fv(cs.uModel, 1, GL_FALSE, &m[0][0]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[obj]);

    glEnableVertexAttribArray(cs.aVertex);
    glVertexAttribPointer(cs.aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, pos));
    glEnableVertexAttribArray(cs.aColor);
    glVertexAttribPointer(cs.aColor, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, rgb));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[objInd]);

    glDrawElements(GL_TRIANGLES, indexes[obj], GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(cs.aVertex);
    glDisableVertexAttribArray(cs.aColor);
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glUseProgram(cs.shader);

    glUniformMatrix4fv(cs.uProjection, 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(cs.uView,       1, GL_FALSE, &view[0][0]);

    models[Box] = glm::rotate(models[Box], .03f, vec3(0.f, 0.f, 1.f));

    drawObj(Bg,        BgInd);
    drawObj(Flour,     FlourInd);
    drawObj(Box,       BoxInd);
    drawObj(BoxHead,   BoxHeadInd, {models[Box]});

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

void deinit(){
    glDeleteBuffers(End, VBOs);
    glDeleteProgram(cs.shader);
    glDeleteProgram(ts.shader);
    glDeleteTextures(End, Textures);
}


