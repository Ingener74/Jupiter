/*
 * GLEngine.h
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#ifndef GLENGINE_H_
#define GLENGINE_H_

#include "IDrawEngine.h"

namespace jupiter
{

class GLEngine: public IDrawEngine
{
public:
	GLEngine();
	virtual ~GLEngine();

	virtual void setCurrentScene(Scene::Ptr);
	virtual void draw();
	virtual void inputToAll(int x, int y);
	virtual void animateAll(double elapsedMs);
};

} /* namespace ndk_game */

#endif /* GLENGINE_H_ */
