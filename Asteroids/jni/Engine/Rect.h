/*
 * Rect.h
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#ifndef RECT_H_
#define RECT_H_

#include <Engine/Common.h>

namespace ndk_game
{

class Rect
{
public:
    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
    virtual ~Rect();

    bool operator||(const Rect&) const;
    bool isInside(int x, int y) const;

    int x1, y1, x2, y2;
};

Rect operator+(const Rect&, const glm::vec3&);
std::ostream& operator<<(std::ostream&, const Rect&);

} /* namespace ndk_game */

#endif /* RECT_H_ */
