/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <array>
#include <vector>
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
void display(void);
void reshape(int w, int h);
void mouse(int button, int action, int x, int y);
void mouseMove(int x, int y);
void timer(int time);

string vs = R"(

varying vec4 color;
void main(){
    gl_Position = gl_Projection * gl_ModelView * gl_Vertex;
    color = gl_Color;
}

)", fs = R"(

varying vec4 color;

void main(){
    gl_FragColor = color;
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

vector<float> flour = {
        -3.f, 3.f, 0.f,   1.f, 1.f, 1.f,
         3.f, 3.f, 0.f,   1.f, 1.f, 1.f,
        -3.f,-3.f, 0.f,   1.f, 1.f, 1.f,
         3.f,-3.f, 0.f,   1.f, 1.f, 1.f,
}, box = {
        -35.f, 9.f, 0.f,   1.f, 1.f, 1.f,
         35.f, 9.f, 0.f,   1.f, 1.f, 1.f,
        -35.f,-9.f, 0.f,   1.f, 1.f, 1.f,
         35.f,-9.f, 0.f,   1.f, 1.f, 1.f,
};

vector<ushort> flourInd = {
        0, 2, 1,   3, 1, 2,
}, boxInd = {
        0, 2, 1,   3, 1, 2,
};

int width = 800, height = 480;

GLuint shader = 0;

enum Objects{
    Flour,
    Box,

    FlourInd,
    BoxInd,

    End
};
GLuint VBOs[2];

mat4 models[End];

mat4 proj, view;

int main(int argc, char **argv) {
    try {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(800, 480);
        glutCreateWindow("Test");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);

        if (glewInit() != GLEW_OK)
            throw runtime_error("glew init error");

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, width, height);

        glutTimerFunc(0, timer, 0);

        glutMainLoop();

        return EXIT_SUCCESS;
    } catch (std::exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}

void init(){
    shader = createProgram(vs, fs);

    proj = glm::perspective(45.f, 800.f / 480.f, 10.f, 10000.f);
    view = lookAt(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 50.f), vec3(0.f, 1.f, 0.f));

    glGenBuffers(End, VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Flour]);
    glBufferData(GL_ARRAY_BUFFER, flour.size() * sizeof(float), flour.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Box]);
    glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(float), box.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[FlourInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, flourInd.size() * sizeof(ushort), flourInd.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxInd]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxInd.size() * sizeof(ushort), boxInd.data(), GL_STATIC_DRAW);
}

void deinit(){
    glDeleteBuffers(End, VBOs);
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glUseProgram(shader);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(M_PI / 4, 800.f / 480.f, 10.f, 10000.f);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.f, 0.f, 0.f,   0.f, 0.f, 50.f,   0.f, 1.f, 0.f);

    {
        // Рисуем пол
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[Flour]);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 6*sizeof(float), static_cast<void*>(0));

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 6*sizeof(float), (void*)(0 + 3*sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[FlourInd]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    {
        // Рисуем коробочку
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[Box]);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 6*sizeof(float), static_cast<void*>(0));

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 6*sizeof(float), (void*)(0 + 3*sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[BoxInd]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
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

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource); // TODO surrount shaders to RAII
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


