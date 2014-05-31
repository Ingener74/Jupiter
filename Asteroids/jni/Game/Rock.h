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

    static Rock::Ptr create(android_app * app, int screenWidth, int screenHeight);

    virtual ~Rock();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

private:
    Rock(android_app * app, int screenWidth, int screenHeight);

    std::list<ndk_game::Sprite::Ptr> _rockParts;
};

#endif /* ROCK_H_ */
