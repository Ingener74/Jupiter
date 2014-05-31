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
    StartButton(android_app * app, int screenWidth,
            ndk_game::IDrawEngine::Ptr engine, ndk_game::Scene::Ptr mainScene);
    virtual ~StartButton()
    {
        ndk_game::Log() << "~StartButton()";
    }

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
private:
    ndk_game::Sprite::Ptr _sb1, _sb2, _cur;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    ndk_game::Rect _buttonRect;

    ndk_game::IDrawEngine::Ptr _engine;
    ndk_game::Scene::Ptr _mainScene;
};

#endif /* STARTBUTTON_H_ */
