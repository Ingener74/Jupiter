
#version 330

uniform mat4 projection, view, model;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 color_;

void main(){
    gl_Position = projection * view * model * position;
    color_ = color;
}


