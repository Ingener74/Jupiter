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

GLfloat
bw       = 136.f,
bh       = 40.f,

b0_off   = 0.f,
b1_off   = 41.f,
b2_off   = 82.f,

ts       = 256.f;

vector<GLfloat> pos012 = {
    -bw/2,  bh/2, 0.f,
     bw/2,  bh/2, 0.f,
    -bw/2, -bh/2, 0.f,
     bw/2, -bh/2, 0.f,
};

vector<GLfloat> texcoord0 = {
    0.f, b0_off,           ts/bw, b0_off,
    0.f, b0_off + bh/ts,   ts/bw, b0_off + bh/ts,
}, texcoord1 = {
    0.f, b1_off,           ts/bw, b1_off,
    0.f, b1_off + bh/ts,   ts/bw, b1_off + bh/ts,
}, texcoord2 = {
    0.f, b2_off,           ts/bw, b2_off,
    0.f, b2_off + bh/ts,   ts/bw, b2_off + bh/ts,
};

vector<uint16_t> indeces = {
    0, 2, 1, 3
};

GLuint shader;

GLuint vaos[3];
GLuint pos;
GLuint texcoords[3];
GLuint indeces_;

GLuint texture;

mat4 proj, view;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
//    proj = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -h/2, h/2);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void init() {

    shader = createProgram(vertex_color, fragment_color);

    glGenBuffers(1, &pos);
    glBindBuffer(GL_ARRAY_BUFFER, pos);
    glBufferData(GL_ARRAY_BUFFER, pos012.size() * sizeof(float), pos012.data(), GL_STATIC_DRAW);

    glGenBuffers(3, texcoords);
    {
        glBindBuffer(GL_ARRAY_BUFFER, texcoords[0]);
        glBufferData(GL_ARRAY_BUFFER, texcoord0.size() * sizeof(float), texcoord0.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texcoords[1]);
        glBufferData(GL_ARRAY_BUFFER, texcoord1.size() * sizeof(float), texcoord1.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texcoords[2]);
        glBufferData(GL_ARRAY_BUFFER, texcoord2.size() * sizeof(float), texcoord2.data(), GL_STATIC_DRAW);
    }

    glGenBuffers(1, &indeces_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeces_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces.size() * sizeof(uint16_t), indeces.data(), GL_STATIC_DRAW);

    glGenVertexArrays(3, vaos);
    {
        glBindVertexArray(vaos[0]);

        glBindBuffer(GL_ARRAY_BUFFER, pos);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, texcoords[0]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeces_);
    }
    {
        glBindVertexArray(vaos[1]);

        glBindBuffer(GL_ARRAY_BUFFER, pos);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, texcoords[1]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeces_);
    }
    {
        glBindVertexArray(vaos[2]);

        glBindBuffer(GL_ARRAY_BUFFER, pos);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, texcoords[2]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeces_);
    }
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glFlush();
    glutSwapBuffers();
}

void deinit() {
}

