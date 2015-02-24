/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <boost/filesystem.hpp>

#include <Jupiter/Game.h>
#include <Jupiter/TextureBuilder.h>
#include <Jupiter/ResourceManager.h>
#include <Jupiter/FileResource.h>
//#include <Jupiter/PNGImageFactory.h>
#include <Jupiter/JupiterError.h>

//#include <Jupiter/FileShaderFactory.h>
//#include <Jupiter/CPPControllerFactory.h>

#include "Factories/ImageTextureFactory.h"

#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;
using namespace glm;

Game::Game()
{
//    int width = 100, height = 100;
//    render = {ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100)};
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Game::~Game()
{
}

void Game::draw()
{
    render.visit(node);
}

void Game::input()
{
}

int32_t Game::getWidth() const
{
    return width;
}

int32_t Game::getHeight() const
{
    return height;
}

} /* namespace jupiter */
