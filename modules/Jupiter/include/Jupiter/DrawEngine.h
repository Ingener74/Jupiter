/*
 * DrawEngine.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef DRAWENGINE_H_
#define DRAWENGINE_H_

#include <Jupiter/Common.h>
#include <Jupiter/Scene.h>
#include <Jupiter/IShaderLoader.h>

namespace jupiter
{

class DrawEngine
{
public:
    using Ptr = std::shared_ptr<DrawEngine>;

    DrawEngine(IShaderLoader::Ptr shaderLoader, const glm::mat4& Ortho, int screenW, int screenH);
    virtual ~DrawEngine();

    virtual void setCurrentScene( Scene::Ptr );
    virtual void draw();
    virtual void inputToAll( int x, int y );
    virtual void animateAll( double elapsedMs );

protected:
    GLuint _program = 0;

    GLuint _uMVP = 0, _aPOS = 0, _aTEX = 0, _uTEX = 0;

    glm::mat4 _ortho;
    int _sW = 0, _sH = 0;

    Scene::Ptr _currentScene;

    static GLuint createProgram( std::string vertexShader, std::string fragmentShader );
    static GLuint createShader( GLenum shaderType, std::string source );
};

} /* namespace jupiter */

#endif /* DRAWENGINE_H_ */
