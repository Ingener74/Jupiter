/*
 * GLEngine.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#include <Jupiter/GLEngine.h>

namespace jupiter
{

GLEngine::GLEngine()
{
}

GLEngine::~GLEngine()
{
}

void GLEngine::setCurrentScene(Scene::Ptr) throw ()
{
}

void GLEngine::draw() throw (std::runtime_error)
{
}

void GLEngine::inputToAll(int x, int y) throw ()
{
}

void GLEngine::animateAll(double elapsedMs) throw (std::runtime_error)
{
}

} /* namespace ndk_game */
