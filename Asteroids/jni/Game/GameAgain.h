/*
 * GameAgain.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef GAMEAGAIN_H_
#define GAMEAGAIN_H_

#include <Engine/Engine.h>
#include <Game/GameBuilder.h>

class GameAgain: public ndk_game::IGameObject
{
public:
    GameAgain(android_app * app, int screenWidth);
    virtual ~GameAgain();

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

    double _fadeOut = 0.0;
};

#endif /* GAMEAGAIN_H_ */
