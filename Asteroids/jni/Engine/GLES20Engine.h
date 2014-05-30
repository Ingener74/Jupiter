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
    GLES20Engine(IShaderLoader::Ptr shaderLoader, const glm::mat4& Ortho);
    virtual ~GLES20Engine();

    virtual void setCurrentScene(Scene::Ptr) throw ();
    virtual void draw() throw (std::runtime_error);
    virtual void inputToAll(int x, int y) throw ();
    virtual void animateAll(double elapsedMs) throw (std::runtime_error);

private:
    GLuint _program;
    GLuint _vs;
    GLuint _fs;

    GLuint _uMVP, _aPOS, _aTEX, _uTEX;

    glm::mat4 _ortho;

    Scene::Ptr _currentScene;

    GLuint createProgram(const char* vertexShader,
            const char* fragmentShader);
    GLuint createShader(GLenum shaderType, const char* source);
};

} /* namespace ndk_game */

#endif /* GLES20ENGINE_H_ */
