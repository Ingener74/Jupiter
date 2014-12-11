/*
 * RightButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef RIGHTBUTTON_H_
#define RIGHTBUTTON_H_

#include <Jupiter/Jupiter.h>
#include <BattleShip.h>

class RightButton: public jupiter::IGameObject
{
public:
    RightButton(int screenWidth, int screenHeight, BattleShip::Ptr);
    virtual ~RightButton();

    virtual void update(double elapsed) ;
    virtual void input(int x, int y) ;
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const ;
    virtual std::string getName() const ;

private:
    std::shared_ptr<jupiter::Sprite> _norm, _pushed, _cur;

#ifdef jupiter_DEBUG
    jupiter::Sprite::Ptr _rect;
#endif

    jupiter::Rect _buttonRect;

    BattleShip::Ptr _bs;

    double _fadeOut;
};

#endif /* RIGHTBUTTON_H_ */
