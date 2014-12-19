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

#include "Factories/ImageTextureFactory.h"

namespace jupiter
{

using namespace std;

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

    cout << __PRETTY_FUNCTION__ << " import " << gameFile << endl;
}

Game::~Game()
{
}

void Game::draw()
{
}

void Game::input()
{
}

} /* namespace jupiter */

