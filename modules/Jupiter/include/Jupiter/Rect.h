/*
 * Rect.h
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#ifndef RECT_H_
#define RECT_H_

#include <iostream>

#include <glm/glm.hpp>

namespace jupiter
{

class Rect
{
public:
    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
    virtual ~Rect() = default;

    bool operator||(const Rect&) const; // intersection operation
    bool isInside(int x, int y) const;

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    friend Rect operator+(const Rect&, const glm::vec3&);

    friend std::ostream& operator<<(std::ostream&, const Rect&);
};


} /* namespace ndk_game */

#endif /* RECT_H_ */
