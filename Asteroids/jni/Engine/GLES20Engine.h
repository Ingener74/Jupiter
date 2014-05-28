/*
 * GLES20Engine.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef GLES20ENGINE_H_
#define GLES20ENGINE_H_

#include <Engine/Common.h>
#include <Engine/IDrawEngine.h>
#include <Engine/IShaderLoader.h>

namespace ndk_game
{

class GLES20Engine: public IDrawEngine
{
public:
    GLES20Engine(IShaderLoader::Ptr);
    virtual ~GLES20Engine();

    virtual void draw(Scene::Ptr) throw (std::runtime_error);

private:
    GLuint _program;
    GLuint _vs;
    GLuint _fs;

    GLuint createProgram(const char* vertexShader,
            const char* fragmentShader);
    GLuint createShader(GLenum shaderType, const char* source);
};

} /* namespace ndk_game */

#endif /* GLES20ENGINE_H_ */
