/*
 * Bullet.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <Engine/Engine.h>

class Bullet: public ndk_game::IGameObject
{
public:
    Bullet(int screenWidth, int screenHeight, float x, float y, float angle);
    virtual ~Bullet();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual ndk_game::Rect getRect() const throw ();

    virtual void collision(IGameObject::Ptr) throw (std::runtime_error);
    virtual bool removeMe() const throw ();

private:
    ndk_game::Sprite::Ptr _bullet;

    glm::vec3 _vel, _pos;
    float _angle = 0.f;

    int _screenWidth = 0, _screenHeight = 0;

    ndk_game::Rect _bulletRect;

    bool _remove = false;
};

#endif /* BULLET_H_ */
