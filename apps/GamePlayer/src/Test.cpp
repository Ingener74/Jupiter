/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

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

using namespace std;
using namespace glm;

GLuint createShader(GLenum shaderType, const string& source);
GLuint createProgram(const string& vertexShaderSource, const string& fragmentShaderSource);


void init();
void deinit();
void display(void);
void reshape(int w, int h);
void mouse(int button, int action, int x, int y);
void mouseMove(int x, int y);
void timer(int time);
void glError();

string vs = R"(

attribute vec4 vertex;
attribute vec4 color;

// uniform   mat4 projection, view, model;
uniform   mat4 projection, model;

varying vec4 vcolor;

void main(){
    // gl_Position = projection * view * model * vertex;
    gl_Position = projection * model * vertex;
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
    float x, y, z;
    float r, g, b;
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
}, bgInd = {
    0, 2, 1,   3, 1, 2,
};

float width = 400.f, height = 240.f;

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
    Bg,

    FlourInd,
    BoxInd,
    BgInd,

    End
};
GLuint VBOs[2];

mat4 models[End];

mat4 proj, view;

int main(int argc, char **argv) {
    try {
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

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Bg]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(float), bg.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[FlourInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, flourInd.size() * sizeof(ushort), flourInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BgInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), bgInd.data(), GL_STATIC_DRAW);

    models[Box] = glm::translate(models[Box], vec3(0.f, 30.f, 0.f));
    models[Flour] = glm::translate(models[Flour], vec3(0.f, -40.f, 0.f));
    models[Bg] = glm::translate(models[Bg], vec3(0.f, 0.f, -1.f));
}

void deinit(){
    glDeleteBuffers(End, VBOs);
}

void drawObj(int obj, int objInd) {
    glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(models[obj]));

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[obj]);

    glEnableVertexAttribArray(aVertex);
    glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(aColor);
    glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (0 + 3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[objInd]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(aVertex);
    glDisableVertexAttribArray(aColor);
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glUseProgram(shader);

    glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(proj));
    glUniformMatrix4fv(uView,       1, GL_FALSE, value_ptr(view));

    drawObj(Bg, BgInd);
    drawObj(Flour, FlourInd);
    drawObj(Box, BoxInd);

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

//    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(0.f, 0.f, 0.f), vec3(0.f, 50.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void mouse(int button, int action, int x, int y) {
}

void mouseMove(int x, int y) {
}

void timer(int time) {

    glutPostRedisplay();

    int delay = 1000 / 30;
    glutTimerFunc(delay, timer, 0);
}

GLuint createProgram(const string& vertexShaderSource, const string& fragmentShaderSource) {
    if (vertexShaderSource.empty())
        throw runtime_error("vertex shader is empty");
    if (fragmentShaderSource.empty())
        throw runtime_error("fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (!program)
        throw runtime_error("can't create program");

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE) {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen) {
            vector<char> buf(bufLen);
            glGetProgramInfoLog(program, bufLen, NULL, buf.data());
            throw runtime_error(string("can't link shader program\n") + buf.data());
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint createShader(GLenum shaderType, const string& source) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader)
        throw runtime_error("can't create shader");

    const char* sourceBuffer = source.c_str();

    glShaderSource(shader, 1, &sourceBuffer, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled)
        return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen)
        throw runtime_error("error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, buf.data());

    static array<string, 2> shaderTypeString = { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw runtime_error(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
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

