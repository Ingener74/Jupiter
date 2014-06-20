/*
 * Rect.cpp
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#include <Engine/Common.h>
#include <Engine/Rect.h>
#include <Engine/Log.h>

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
        ((n.x1 > std::min(x1, x2) && n.x1 < std::max(x1, x2)) || (n.x2 > std::min(x1, x2) && n.x2 < std::max(x1, x2))) &&
        ((n.y1 > std::min(y1, y2) && n.y1 < std::max(y1, y2)) || (n.y2 > std::min(y1, y2) && n.y2 < std::max(y1, y2)))
    );
}

bool Rect::isInside(int x, int y) const
{
    return
    (
        (x > std::min(x1, x2) && x < std::max(x1, x2)) &&
        (y > std::min(y1, y2) && y < std::max(y1, y2))
    );
}

Rect operator +(const Rect& r, const glm::vec3& v)
{
    Rect res;
    res.x1 = r.x1 + v.x;
    res.x2 = r.x2 + v.x;
    res.y1 = r.y1 + v.y;
    res.y2 = r.y2 + v.y;
    return res;
}

std::ostream& operator <<(std::ostream& sout, const Rect& r)
{
    sout << "Rect: " <<
            r.x1 << " x " << r.y1 << " -> " <<
            r.x2 << " x " << r.y2 << ", " <<
            std::max(r.x1, r.x2) - std::min(r.x1, r.x2) << " x " <<
            std::max(r.y1, r.y2) - std::min(r.y1, r.y2);
    return sout;
}

} /* namespace ndk_game */

