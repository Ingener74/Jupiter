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

    virtual void setCurrentScene(Scene::Ptr) throw ();
    virtual void draw() throw (std::runtime_error);
    virtual void inputToAll(int x, int y) throw ();
    virtual void animateAll(double elapsedMs) throw (std::runtime_error);
};

} /* namespace ndk_game */

#endif /* GLENGINE_H_ */
