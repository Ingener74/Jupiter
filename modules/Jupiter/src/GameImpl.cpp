/*
 * GameImpl.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <Jupiter/GameImpl.h>

namespace jupiter
{

GameImpl::GameImpl(Node node, int32_t width, int32_t height): node(node), width(width), height(height)
{
}

GameImpl::~GameImpl()
{
}

Node& GameImpl::getRootNode()
{
    return node;
}

int32_t GameImpl::getWidth() const
{
    return width;
}

int32_t GameImpl::getHeight() const
{
    return height;
}

} /* namespace jupiter */
