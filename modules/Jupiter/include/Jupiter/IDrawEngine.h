/*
 * IDrawEngine.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef IDRAWENGINE_H_
#define IDRAWENGINE_H_

#include <Jupiter/Common.h>
#include <Jupiter/Scene.h>

namespace jupiter
{

class IDrawEngine
{
public:
	using Ptr = std::shared_ptr<IDrawEngine>;

	virtual ~IDrawEngine();

	virtual void setCurrentScene(Scene::Ptr);
	virtual void draw();
	virtual void inputToAll(int x, int y);
	virtual void animateAll(double elapsedMs);

protected:
	IDrawEngine();

	static GLuint createProgram(std::string vertexShader, std::string fragmentShader);
	static GLuint createShader(GLenum shaderType, std::string source);
};

} /* namespace jupiter */

#endif /* IDRAWENGINE_H_ */
