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
#include <Jupiter/PNGImageFactory.h>
#include <Jupiter/JupiterError.h>

#include <Jupiter/FileShaderFactory.h>
#include <Jupiter/CPPControllerFactory.h>

#include "Factories/ImageTextureFactory.h"

#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;
using namespace glm;

Game::Game()
{
}

Game::Game(const std::string& gameFile) :
        _impl(Builder<Game, GameImpl>::create(boost::filesystem::path(gameFile).filename().c_str()))
{
    int width = 100, height = 100;
    _render = {ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100)};
}

Game::~Game()
{
}

void Game::draw()
{
    if (_impl)
        _render.visit(_impl->getRootNode());
    else
        throw JupiterError("game impl is invalid");
}

void Game::input()
{
}

int32_t Game::width() const
{
    return _impl ? _impl->getWidth() : throw JupiterError("game impl is invalid");
}

int32_t Game::height() const
{
    return _impl ? _impl->getHeight() : throw JupiterError("game impl is invalid");
}

} /* namespace jupiter */

