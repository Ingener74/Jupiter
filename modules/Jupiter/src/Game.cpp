/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <Jupiter/facade/Game.h>
#include <Jupiter/detail/TextureBuilder.h>

#include "Factories/ImageTextureFactory.h"

namespace jupiter
{

using namespace std;

Game::Game()
{
}

Game::Game( const std::string& gameFile )
{
    TextureBuilder::addFactory("file", make_shared<ImageTextureFactory>());
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

