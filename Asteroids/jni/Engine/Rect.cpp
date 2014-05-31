/*
 * Rect.cpp
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#include <Engine/Common.h>
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

bool Rect::operator ||(const Rect& n) const
{
    return
    (
        (n.x1 > std::min(x1, x2) && n.x1 < std::max(x1, x2)) ||
        (n.x2 > std::min(x1, x2) && n.x2 < std::max(x1, x2)) ||
        (n.y1 > std::min(y1, y2) && n.y1 < std::max(y1, y2)) ||
        (n.y2 > std::min(y1, y2) && n.y2 < std::max(y1, y2))
    );
}

bool Rect::isInside(int x, int y) const
{
    return
    (
        (x > std::min(x1, x2) && x < std::max(x1, x2)) ||
        (y > std::min(y1, y2) && y < std::max(y1, y2))
    );
}

} /* namespace ndk_game */

