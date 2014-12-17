/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <Jupiter/facade/Game.h>
#include <Jupiter/detail/TextureBuilder.h>
#include <Jupiter/ResourceManager.h>
#include <Jupiter/detail/FileSpriteFactory.h>
#include <Jupiter/detail/PNGImageFactory.h>

#include "Factories/ImageTextureFactory.h"

namespace jupiter
{

using namespace std;

Game::Game(): Game("fake")
{
}

Game::Game( const std::string& gameFile )
{
    TextureBuilder::addFactory("file", make_shared<ImageTextureFactory>());

//    ResourceManager::setPathPrefix(gameFileLocation.parent_path().c_str());
//    ResourceManager::setFactory(make_shared<FileResource>());

    ImageBuilder::addFactory("png", make_shared<PNGImageFactory>());
    ImageBuilder::addFactory("PNG", make_shared<PNGImageFactory>());

    SpriteBuilder::addFactory("file", make_shared<FileSpriteFactory>());
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

