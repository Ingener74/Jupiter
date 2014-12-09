/*
 * RightButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef RIGHTBUTTON_H_
#define RIGHTBUTTON_H_

#include <Engine/Engine.h>
#include <Game/BattleShip.h>

class RightButton: public ndk_game::IGameObject
{
public:
    RightButton(int screenWidth, int screenHeight, BattleShip::Ptr);
    virtual ~RightButton();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

private:
    ndk_game::Sprite::Ptr _norm, _pushed, _cur;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    ndk_game::Rect _buttonRect;

    BattleShip::Ptr _bs;

    double _fadeOut;
};

#endif /* RIGHTBUTTON_H_ */
