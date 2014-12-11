/*
 * FireButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef FIREBUTTON_H_
#define FIREBUTTON_H_

#include <Jupiter/Jupiter.h>
#include <BattleShip.h>

class FireButton: public jupiter::IGameObject
{
public:
    FireButton(int screenWidth, int screenHeight, BattleShip::Ptr);
    virtual ~FireButton();

    virtual void update(double elapsed) ;
    virtual void input(int x, int y) ;
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const ;
    virtual std::string getName() const ;

private:
    std::shared_ptr<jupiter::Sprite> _norm, _pushed, _cur;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    jupiter::Rect _buttonRect;

    BattleShip::Ptr _bs;
    double _fadeOut;
};

#endif /* FIREBUTTON_H_ */
