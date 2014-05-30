/*
 * Rect.h
 *
 *  Created on: May 30, 2014
 *      Author: ingener
 */

#ifndef RECT_H_
#define RECT_H_

namespace ndk_game
{

class Rect
{
public:
    Rect(int x1, int y1, int x2, int y2);
    virtual ~Rect();

    bool operator||(const Rect&);

private:
    int x1, y1, x2, y2;
};

} /* namespace ndk_game */

#endif /* RECT_H_ */
