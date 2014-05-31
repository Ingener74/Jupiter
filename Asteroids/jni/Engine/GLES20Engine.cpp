/*
 * GLES20Engine.cpp
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#include <Engine/GLES20Engine.h>
#include <Engine/Log.h>
#include <Engine/Tools.h>

namespace ndk_game
{

GLES20Engine::GLES20Engine(IShaderLoader::Ptr sl, const glm::mat4& ortho, int screenW, int screenH) :
        _program(0), _vs(0), _fs(0), _uMVP(0), _aPOS(0), _aTEX(0), _uTEX(0), _ortho(
                ortho), _sW(screenW), _sH(screenH)
{
    _program = createProgram(sl->getVertexShader(), sl->getFragmentShader());

    _uMVP = glGetUniformLocation(_program, "uMVP");
    _aPOS = glGetAttribLocation(_program, "aPOS");
    _aTEX = glGetAttribLocation(_program, "aTEX");
    _uTEX = glGetUniformLocation(_program, "uTEX");
}

GLES20Engine::~GLES20Engine()
{
    Log() << "GLES20Engine::~GLES20Engine()";
    glDeleteProgram(_program);
    glDeleteShader(_vs);
    glDeleteShader(_fs);
}

void GLES20Engine::setCurrentScene(Scene::Ptr s) throw ()
{
    _currentScene = s;
}

void GLES20Engine::draw() throw (std::runtime_error)
{
    glUseProgram(_program);
    Tools::glError();

    for (auto &gameObj : _currentScene->gameObject)
    {
        glActiveTexture(GL_TEXTURE0);

        for (auto &sprite : gameObj->getSprites())
        {
            sprite->getTexture()->bind();

            glUniform1i(_uTEX, 0);
            glEnableVertexAttribArray(_aPOS);
            glEnableVertexAttribArray(_aTEX);

            GLfloat * spriteVertex = sprite->getVertex();
            uint32_t spriteVertexCount = sprite->getVertexCount();

            glVertexAttribPointer(_aPOS, 3, GL_FLOAT, GL_FALSE,
                    5 * sizeof(GLfloat), &spriteVertex[0]);
            glVertexAttribPointer(_aTEX, 2, GL_FLOAT, GL_FALSE,
                    5 * sizeof(GLfloat), &spriteVertex[3]);

            glm::mat4 mvp = _ortho * sprite->getModelMatrix();
            glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

            GLenum drawType;
            switch (sprite->getDrawType())
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
    }

    glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(_ortho));
}

void GLES20Engine::inputToAll(int x, int y) throw ()
{
    for (auto gameObj : _currentScene->gameObject)
    {
        gameObj->input(x - _sW/2, _sH/2 - y);
    }
}

void GLES20Engine::animateAll(double elapsedMs) throw (std::runtime_error)
{
    for (auto gameObj : _currentScene->gameObject)
    {
        gameObj->update(elapsedMs);
    }
}

GLuint GLES20Engine::createShader(GLenum shaderType, const char* source)
{
    GLuint shader = glCreateShader(shaderType);
    if (!shader) throw std::runtime_error("can't create shader");

    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled) return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen) throw std::runtime_error("error in create shader");

    std::unique_ptr<char> buf(new char[infoLen]);
    glGetShaderInfoLog(shader, infoLen, 0, buf.get());

    throw std::runtime_error(buf.get());
}

GLuint GLES20Engine::createProgram(const char* vertexShader,
        const char* fragmentShader)
{
    _vs = createShader(GL_VERTEX_SHADER, vertexShader);
    _fs = createShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLuint program = glCreateProgram();
    if (!program) throw std::runtime_error("can't create program");

    glAttachShader(program, _vs);
    glAttachShader(program, _fs);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen)
        {
            std::unique_ptr<char> buf(new char[bufLen]);
            glGetProgramInfoLog(program, bufLen, NULL, buf.get());
            throw std::runtime_error(buf.get());
        }
    }
    return program;
}

} /* namespace ndk_game */
