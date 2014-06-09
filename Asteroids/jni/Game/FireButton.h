/*
 * FireButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef FIREBUTTON_H_
#define FIREBUTTON_H_

#include <Engine/Engine.h>
#include <Game/BattleShip.h>

class FireButton: public ndk_game::IGameObject
{
public:
    FireButton(int screenWidth, int screenHeight, BattleShip::Ptr);
    virtual ~FireButton();

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

#endif /* FIREBUTTON_H_ */
