/*
 * Explosion.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include <Engine/Engine.h>
#include <Game/GameBuilder.h>

class Explosion: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<Explosion>;

    Explosion(android_app * app, int screenWidth, int screenHeight, float x, float y);
    virtual ~Explosion();

    Explosion::Ptr clone(float x, float y);

    static std::vector<ndk_game::Sprite::Ptr> createSprites(android_app* , int screenWidth, int screenHeight);

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual bool removeMe() const throw ();

private:
    std::vector<ndk_game::Sprite::Ptr> _expSprites;
    ndk_game::Sprite::Ptr _curSprite;

    float _x, _y;
    int _currentSprite;
    bool _remove;
    float _delta;
};

#endif /* EXPLOSION_H_ */
