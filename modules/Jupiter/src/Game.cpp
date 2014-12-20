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

Game::Game(): Game("fake")
{
}

Game::Game( const std::string& gameFile )
{
    boost::filesystem::path game{gameFile};

    TextureBuilder::addFactory("file", make_shared<ImageTextureFactory>());

    ResourceManager::setPathPrefix(game.parent_path().c_str());
    ResourceManager::setFactory(make_shared<FileResource>());

    ImageBuilder::addFactory("png", make_shared<PNGImageFactory>());
    ImageBuilder::addFactory("PNG", make_shared<PNGImageFactory>());

    Builder<Shader, ShaderImpl>::addFactory("file", make_shared<FileShaderFactory>());

    Builder<Controller, ControllerImpl>::addFactory("c++", make_shared<CPPControllerFactory>());

    _rootNode = {"root"};

    int width = 100, height = 100;
    _render = { ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100) };
}

Game::~Game()
{
}

void Game::draw()
{
    _render.visit(_rootNode);
}

void Game::input()
{
}

int32_t Game::width() const
{
    return 100;
}

int32_t Game::height() const
{
    return 100;
}

} /* namespace jupiter */

