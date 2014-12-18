/*
 * StartButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef STARTBUTTON_H_
#define STARTBUTTON_H_

#include <Jupiter.h>
#include <Tools.h>

class StartButton: public jupiter::IGameObject
{
public:
    StartButton(int screenWidth, int screenHeight, GameTools);
    virtual ~StartButton();

    virtual void update(double elapsed);
    virtual void input(int x, int y);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const;
    virtual std::string getName() const;

private:
    std::shared_ptr<jupiter::Sprite> _sb1, _sb2, _cur;

#ifdef NDK_GAME_DEBUG
    jupiter::Sprite::Ptr _rect;
#endif

    jupiter::Rect _buttonRect;

    double _fadeOut;
    GameTools _tools;
};

#endif /* STARTBUTTON_H_ */
