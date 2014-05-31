/*
 * LeftButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef LEFTBUTTON_H_
#define LEFTBUTTON_H_

#include <Engine/Engine.h>
#include <Game/BattleShip.h>

class LeftButton: public ndk_game::IGameObject
{
public:
    LeftButton(android_app *, int screenWidth, int screenHeight, BattleShip::Ptr);
    virtual ~LeftButton();

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

#endif /* LEFTBUTTON_H_ */
