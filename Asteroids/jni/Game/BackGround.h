/*
 * BackGround.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <Engine/Engine.h>

class BackGround: public ndk_game::IGameObject
{
public:
    BackGround(android_app * app, int screenWidth);
    virtual ~BackGround();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

private:
    ndk_game::Sprite::Ptr _bg;
};

#endif /* BACKGROUND_H_ */
