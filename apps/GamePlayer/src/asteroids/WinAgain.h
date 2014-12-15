/*
 * WinAgain.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef WINAGAIN_H_
#define WINAGAIN_H_

#include <Jupiter.h>
#include <Tools.h>

class WinAgain: public jupiter::IGameObject
{
public:
    WinAgain(int screenWidth, GameTools, std::function<void()> newGame);
    virtual ~WinAgain();

    virtual void update(double elapsed);
    virtual void input(int x, int y);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const;
    virtual std::string getName() const;

private:
    std::shared_ptr<jupiter::Sprite> _norm, _pushed, _cur;

#ifdef jupiter_DEBUG
    jupiter::Sprite::Ptr _rect;
#endif

    jupiter::Rect _buttonRect;

    double _fadeOut = 0.0;
    std::function<void()> _newGame;
    GameTools _tools;
};

#endif /* WINAGAIN_H_ */
