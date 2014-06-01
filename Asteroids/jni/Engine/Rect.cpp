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
    /*
            06-01 18:27:59.279: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 269 x -165 -> 447 x 12, 178 x 177
            06-01 18:27:59.300: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 269 x -164 -> 447 x 13, 178 x 177
            06-01 18:27:59.310: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 270 x -163 -> 448 x 14, 178 x 177
            06-01 18:27:59.330: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 271 x -163 -> 449 x 14, 178 x 177
            06-01 18:27:59.350: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 272 x -162 -> 450 x 15, 178 x 177
            06-01 18:27:59.360: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 272 x -161 -> 450 x 16, 178 x 177
            06-01 18:27:59.380: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 273 x -161 -> 451 x 16, 178 x 177
            06-01 18:27:59.400: D/Asteroids(5304): battle ship collision Rect: -31 x -31 -> 31 x 31, 62 x 62  ===  Rect: 274 x -160 -> 452 x 17, 178 x 177


            06-01 18:38:25.891: D/Asteroids(7099): battle ship collision Rect: -31 x -354 -> 31 x -319, 62 x 35  ===  Rect: -149 x -521 -> 28 x -343, 177 x 178
            06-01 18:38:25.911: D/Asteroids(7099): battle ship collision Rect: -31 x -381 -> 31 x -346, 62 x 35  ===  Rect: -148 x -520 -> 29 x -342, 177 x 178
            06-01 18:38:26.041: D/Asteroids(7099): battle ship collision Rect: -31 x -534 -> 31 x -499, 62 x 35  ===  Rect: -148 x -516 -> 29 x -338, 177 x 178

    */

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

Rect& Rect::operator +(const glm::vec3& v)
{
    x1 += v.x;
    x2 += v.x;
    y1 += v.y;
    y2 += v.y;
    return *this;
}

Rect operator +(const Rect& r, const glm::vec3& v)
{
    Rect res = r;
    res + v;
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

