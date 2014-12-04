/*
 * DrawEngine.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Jupiter/JupiterError.h>
#include <Jupiter/DrawEngine.h>
#include <Jupiter/Tools.h>
#include <Jupiter/Sprite.h>
#include <Jupiter/IShaderLoader.h>
#include <Jupiter/IGameObject.h>
#include <Jupiter/Scene.h>
#include <Jupiter/Texture.h>

namespace jupiter
{

using namespace std;

DrawEngine::DrawEngine(shared_ptr<IShaderLoader> sl, const glm::mat4& ortho, int screenW, int screenH)
{
    _program = createProgram(sl->getVertexShader(), sl->getFragmentShader());

    _uMVP = glGetUniformLocation(_program, "uMVP");
    _aPOS = glGetAttribLocation(_program, "aPOS");
    _aTEX = glGetAttribLocation(_program, "aTEX");
    _uTEX = glGetUniformLocation(_program, "uTEX");
}

DrawEngine::~DrawEngine()
{
    glDeleteProgram(_program);
    cout << __PRETTY_FUNCTION__ << endl;
}

void DrawEngine::setCurrentScene(shared_ptr<Scene> s)
{
    if (!s) throw JupiterError("set current scene null");
    _currentScene = s;
}

void DrawEngine::draw()
{
    glUseProgram(_program);
    Tools::glError();

    list<shared_ptr<Sprite>> sprites;

    if (!_currentScene) throw JupiterError("engine has no scenes");

    for (auto go : _currentScene->gameObject)
        for (auto s : go->getSprites())
            sprites.push_back(s);

    glActiveTexture(GL_TEXTURE0);

    for (auto s : sprites)
    {
        if (!s->getTexture()) throw JupiterError("empty texture");
        s->getTexture()->bind();

        glUniform1i(_uTEX, 0);
        glEnableVertexAttribArray(_aPOS);
        glEnableVertexAttribArray(_aTEX);

        const GLfloat * spriteVertex = s->getVertex();
        uint32_t spriteVertexCount = s->getVertexCount();

        glVertexAttribPointer(_aPOS, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[0]);
        glVertexAttribPointer(_aTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[3]);

        glm::mat4 mvp = _ortho * s->getModelMatrix();
        glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

        GLenum drawType;
        switch (s->getDrawType())
        {
        case ISpriteLoader::SpriteType::Triangles:
            drawType = GL_TRIANGLES;
            break;
        case ISpriteLoader::SpriteType::TriangleFan:
            drawType = GL_TRIANGLE_FAN;
            break;
        case ISpriteLoader::SpriteType::TriangleStrip:
            drawType = GL_TRIANGLE_STRIP;
            break;
        case ISpriteLoader::SpriteType::LineStrip:
            drawType = GL_LINE_STRIP;
            break;
        default:
            break;
        }
        glDrawArrays(drawType, 0, spriteVertexCount);

        glDisableVertexAttribArray(_aPOS);
        glDisableVertexAttribArray(_aTEX);
    }

    glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(_ortho));
}

void DrawEngine::inputToAll(int x, int y)
{
    for (auto gameObj : _currentScene->gameObject)
    {
        if (!gameObj) throw JupiterError("input to all invalid game object");

        gameObj->input(x - _sW / 2, _sH / 2 - y);
    }
}

void DrawEngine::animateAll(double elapsedMs)
{
    for (auto gameObj : _currentScene->gameObject)
    {
        gameObj->update(elapsedMs);
    }

    for (auto go1 : _currentScene->gameObject)
    {
        for (auto go2 : _currentScene->gameObject)
        {
            if (go1 == go2) continue;
            go1->collision(go2);
        }
    }

    list<shared_ptr<IGameObject>> gameObjs;
    for (auto o : _currentScene->gameObject)
    {
        if (!o->removeMe()) gameObjs.push_back(o);
    }
    _currentScene->gameObject = gameObjs;
}

GLuint DrawEngine::createProgram(string vertexShaderSource, string fragmentShaderSource)
{
    if (vertexShaderSource.empty()) throw JupiterError("vertex shader is empty");
    if (fragmentShaderSource.empty()) throw JupiterError("fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource); // TODO surrount shaders to RAII
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (!program) throw JupiterError("can't create program");

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen)
        {
            vector<char> buf(bufLen);
            glGetProgramInfoLog(program, bufLen, NULL, &buf.front());
            throw JupiterError(string("can't link shader program\n") + &buf.front());
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint DrawEngine::createShader(GLenum shaderType, string source)
{
    GLuint shader = glCreateShader(shaderType);
    if (!shader) throw JupiterError("can't create shader");

    const char* source_buffer = source.c_str();

    glShaderSource(shader, 1, &source_buffer, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled) return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen) throw JupiterError("error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, &buf.front());

    static array<string, 2> shaderTypeString =
    { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw JupiterError(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
}

}  // namespace jupiter

