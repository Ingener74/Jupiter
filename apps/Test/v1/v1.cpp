/*
 * v1.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

#include "main.h"

using namespace std;
using namespace glm;

string coloredSpriteVertex = R"(

#version 120

uniform   mat4 projection, view, model;

attribute vec4 vertex;
attribute vec4 color;

varying vec4 vcolor;

void main(){
    gl_Position = projection * view * model * vertex;
    vcolor = color;
}

)", coloredSpriteFragment = R"(

#version 120

varying vec4 vcolor;

void main(){
    gl_FragColor = vcolor;
}

)", texturedSpriteVertex = R"(

#version 120

uniform   mat4 projection, view, model;

attribute vec4 vertex;
attribute vec2 texcoord;

varying vec2 vtexcoord;

void main(){
    gl_Position = projection * view * model * vertex;
    vtexcoord = texcoord;
}

)", texturedSpriteFragment = R"(

#version 120

varying vec2 vtexcoord;

uniform sampler2D texture;

void main(){
    gl_FragColor = texture2D(texture, vtexcoord);
}

)";

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
    0, 2, 1, 3
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

unique_ptr<ColoredSprite> boxSprite, flourSprite, bgSprite, boxHeadSprite;
unique_ptr<TexturedSprite> tBoxSprite, ship;

mat4 proj, view;

string boxImage, shipImage;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    proj = glm::perspective(45.f, w / float(h), 10.f, 10000.f);
    view = glm::lookAt<float>(vec3(40.f, 40.f, 100.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
}

void init(){

    boxImage        = getBase() + "/Resources/box.png";
    shipImage       = getBase() + "/Resources/ship1.png";

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

    tBoxSprite     = make_unique_<TexturedSprite>(ts, tBox,     tBoxInd,     GL_TRIANGLES, loadTexture(boxImage));
    ship           = make_unique_<TexturedSprite>(ts, shipVerteces, shipTexCoords, shipIndices, GL_TRIANGLE_STRIP, loadTexture(shipImage));

    boxSprite->model        = glm::translate(boxSprite->model,     vec3(0.f,  30.f,  0.f));
    boxHeadSprite->model    = glm::translate(boxHeadSprite->model, vec3(0.f,  3.0f,  0.f));
    flourSprite->model      = glm::translate(flourSprite->model,   vec3(0.f, -40.f,  0.f));
    bgSprite->model         = glm::translate(bgSprite->model,      vec3(0.f,   0.f, -1.f));
    tBoxSprite->model       = glm::translate(tBoxSprite->model,    vec3(0.f, -13.f,  4.f));

    ship->model             = glm::translate(ship->model,          vec3(0.f,  -20.f,  5.f));
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

void deinit(){
    glDeleteProgram(cs.shader);
    glDeleteProgram(ts.shader);

    boxSprite.reset();
    bgSprite.reset();
    flourSprite.reset();
    boxHeadSprite.reset();
    tBoxSprite.reset();
}
