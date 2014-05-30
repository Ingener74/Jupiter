/*
 * Rect.cpp
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#include <Engine/Rect.h>

namespace ndk_game
{

Rect::Rect(int x1, int y1, int x2, int y2) :
        x1(x1), y1(y1), x2(x2), y2(y2)
{
}

Rect::~Rect()
{
}

bool Rect::operator ||(const Rect&)
{
    return (false);
}

} /* namespace ndk_game */

