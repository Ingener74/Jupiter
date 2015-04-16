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

unique_ptr<Program> texturedProgram;

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
}

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.1f, 1.f);

    glFlush();
    glutSwapBuffers();
}

void deinit() {
}

