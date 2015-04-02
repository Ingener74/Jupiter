/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <numeric>
#include <iomanip>
#include <array>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"

using namespace std;
using namespace glm;


void init();
void deinit();
void display(void);
void reshape(int w, int h);
void mouse(int button, int action, int x, int y);
void mouseMove(int x, int y);
void timer(int time);
void glError();

ostream& operator<<(ostream& out, const mat4& r){
    auto t = transpose(r);
    return out << endl <<
        "[" << setw(10) << t[0][0] << ", " << setw(10) << t[0][1] << ", " << setw(10) << t[0][2] << ", " << setw(10) << t[0][3] << ";" << endl <<
        " " << setw(10) << t[1][0] << ", " << setw(10) << t[1][1] << ", " << setw(10) << t[1][2] << ", " << setw(10) << t[1][3] << ";" << endl <<
        " " << setw(10) << t[2][0] << ", " << setw(10) << t[2][1] << ", " << setw(10) << t[2][2] << ", " << setw(10) << t[2][3] << ";" << endl <<
        " " << setw(10) << t[3][0] << ", " << setw(10) << t[3][1] << ", " << setw(10) << t[3][2] << ", " << setw(10) << t[3][3] << "]" << endl;
}

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

string vs = R"(

attribute vec4 vertex;
attribute vec4 color;

uniform   mat4 projection, view, model;

varying vec4 vcolor;

void main(){
    gl_Position = projection * view * model * vertex;
    vcolor = color;
}

)", fs = R"(

varying vec4 vcolor;

void main(){
    gl_FragColor = vcolor;
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

struct Vertex{
    vec3 pos, rgb;
};

vector<float> flour = {
    -35.f, 9.f, 0.f,   .5f, .4f, .1f,
     35.f, 9.f, 0.f,   .5f, .4f, .1f,
    -35.f,-9.f, 0.f,   .5f, .4f, .1f,
     35.f,-9.f, 0.f,   .5f, .4f, .1f,
}, box = {
    -3.f, 3.f, 0.f,   .3f, .6f, .1f,
     3.f, 3.f, 0.f,   .3f, .6f, .1f,
    -3.f,-3.f, 0.f,   .3f, .6f, .1f,
     3.f,-3.f, 0.f,   .3f, .6f, .1f,
}, boxHead = {
    -3.f, 3.f, 0.f,   .3f, .6f, .8f,
     3.f, 3.f, 0.f,   .3f, .6f, .4f,
    -3.f,-3.f, 0.f,   .3f, .6f, .8f,
}, bg = {
    -100.f, 40.f, 0.f,   .7f, .7f, .7f,
     100.f, 40.f, 0.f,   .7f, .7f, .7f,
    -100.f,-40.f, 0.f,   .7f, .7f, .7f,
     100.f,-40.f, 0.f,   .7f, .7f, .7f,
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

float width = 400.f, height = 240.f;
// float width = 800.f, height = 480.f;

GLuint
    shader = 0,
    aVertex = 0,
    aColor = 0,
    uProjection = 0,
    uView = 0,
    uModel = 0;

enum Objects{
    Flour,
    Box,
    BoxHead,
    Bg,

    FlourInd,
    BoxInd,
    BoxHeadInd,
    BgInd,

    End
};
GLuint VBOs[End];
size_t indexes[End];
mat4 models[End];

mat4 proj, view;

int main(int argc, char **argv) {
    try {
        cout << "test " << sizeof(Vertex) << " " << sizeof(float) * 6 << endl;

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
    shader = createProgram(vs, fs);

    uProjection = glGetUniformLocation(shader, "projection");
    uView       = glGetUniformLocation(shader, "view");
    uModel      = glGetUniformLocation(shader, "model");

    aVertex     = glGetAttribLocation(shader, "vertex");
    aColor      = glGetAttribLocation(shader, "color");

    glGenBuffers(End, VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Flour]);
    glBufferData(GL_ARRAY_BUFFER, flour.size() * sizeof(float), flour.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Box]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(float), box.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[BoxHead]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(float), boxHead.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Bg]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(float), bg.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[FlourInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, flourInd.size() * sizeof(ushort), flourInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxHeadInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxHeadInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BgInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), bgInd.data(), GL_STATIC_DRAW);

    indexes[Flour]     = flourInd.size();
    indexes[Box]       = boxInd.size();
    indexes[BoxHead]   = boxHeadInd.size();
    indexes[Bg]        = bgInd.size();

    models[Box]        = glm::translate(models[Box],     vec3(0.f, 30.f, 0.f));
    models[BoxHead]    = glm::translate(models[BoxHead], vec3(0.f, 3.f, 0.f));
    models[Flour]      = glm::translate(models[Flour],   vec3(0.f, -40.f, 0.f));
    models[Bg]         = glm::translate(models[Bg],      vec3(0.f, 0.f, -1.f));
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
//    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 200.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void drawObj(int obj, int objInd, const vector<mat4>& parentsModels = {}) {

    if (parentsModels.empty()) {
        glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(models[obj]));
    } else {
        auto m = accumulate(parentsModels.begin() + 1, parentsModels.end(), parentsModels.front(), multiplies<mat4>());
        m = m * models[obj];
        glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(m));
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[obj]);

    glEnableVertexAttribArray(aVertex);
    glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(aColor);
    glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (0 + 3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[objInd]);

    glDrawElements(GL_TRIANGLES, indexes[obj], GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(aVertex);
    glDisableVertexAttribArray(aColor);
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glUseProgram(shader);

    glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(proj));
    glUniformMatrix4fv(uView,       1, GL_FALSE, value_ptr(view));

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
    glDeleteProgram(shader);
}

void glError()
{
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        stringstream s;
        s << "glGetError: " << hex << error << gluErrorString(error);
        string res = s.str();
        throw runtime_error(res);
    }
}

