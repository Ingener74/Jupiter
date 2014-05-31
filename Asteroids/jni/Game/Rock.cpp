/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/Rock.h>

Rock::Rock()
{
}

Rock::~Rock()
{
}

void Rock::update(double elapsed) throw (std::runtime_error)
{
}

void Rock::input(int x, int y) throw (std::runtime_error)
{
}

std::list<ndk_game::Sprite::Ptr> Rock::getSprites() const throw ()
{
}

std::string Rock::getName() const throw ()
{
    return "Rock";
}
