/*
 * Rock.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef ROCK_H_
#define ROCK_H_

#include <Engine/Engine.h>

class Rock: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<Rock>;

    Rock(android_app * app, int screenWidth, int screenHeight);

    virtual ~Rock();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual void collision(IGameObject::Ptr) throw (std::runtime_error);
    virtual bool removeMe() const throw ();

    virtual ndk_game::Rect getRect() const;

private:
    ndk_game::Sprite::Ptr _rock;

    glm::vec3 _vel, _pos;
    float _angle;

    int _screenWidth, _screenHeight;
    bool _crash;

    ndk_game::Rect _rockRect;
#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif
};

#endif /* ROCK_H_ */
