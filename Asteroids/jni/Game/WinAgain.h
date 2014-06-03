/*
 * WinAgain.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef WINAGAIN_H_
#define WINAGAIN_H_

#include <Engine/Engine.h>
#include <Game/GameBuilder.h>

class WinAgain: public ndk_game::IGameObject
{
public:
    WinAgain(android_app * app, int screenWidth,
            std::weak_ptr<ndk_game::IDrawEngine> engine,
            std::weak_ptr<ndk_game::Scene> mainScene,
            GameBuilder* game
            );
    virtual ~WinAgain();

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

    std::weak_ptr<ndk_game::IDrawEngine> _engine;
    std::weak_ptr<ndk_game::Scene> _mainScene;

    GameBuilder* _game;

    double _fadeOut;
};

#endif /* WINAGAIN_H_ */
