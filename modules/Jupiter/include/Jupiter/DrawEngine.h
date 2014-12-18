/*
 * DrawEngine.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef DRAWENGINE_H_
#define DRAWENGINE_H_

#include <memory>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <Jupiter/Node.h>

namespace jupiter
{

class Scene;

class IShaderLoader;

class DrawEngine
{
public:
    DrawEngine(std::shared_ptr<IShaderLoader>, const glm::mat4& Ortho, int screenWidth, int screenHeight);
    virtual ~DrawEngine();

    virtual void setCurrentScene(std::shared_ptr<Scene>);
    virtual void setRootNode(const Node&);
    virtual void draw();
    virtual void inputToAll(int x, int y);
    virtual void animateAll(double elapsedMs);

protected:
    GLuint _program = 0;

    GLuint _uMVP = 0, _aPOS = 0, _aTEX = 0, _uTEX = 0;

    glm::mat4 _ortho;
    int _screenWidth = 0, _screenHeight = 0;

    std::shared_ptr<Scene> _currentScene;

    Node _rootNode;

    static GLuint createProgram(std::string vertexShader, std::string fragmentShader);
    static GLuint createShader(GLenum shaderType, std::string source);
};

} /* namespace jupiter */

#endif /* DRAWENGINE_H_ */
