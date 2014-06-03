/*
 * StartButton.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef STARTBUTTON_H_
#define STARTBUTTON_H_

#include <Engine/Engine.h>

class StartButton: public ndk_game::IGameObject
{
public:
    StartButton(android_app * app, int screenWidth, int screenHeight,
            std::weak_ptr<ndk_game::IDrawEngine> engine,
            std::weak_ptr<ndk_game::Scene> mainScene);
    virtual ~StartButton();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

private:
    ndk_game::Sprite::Ptr _sb1, _sb2, _cur;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    ndk_game::Rect _buttonRect;

    std::weak_ptr<ndk_game::IDrawEngine> _engine;
    std::weak_ptr<ndk_game::Scene> _mainScene;

    double _fadeOut;
};

#endif /* STARTBUTTON_H_ */