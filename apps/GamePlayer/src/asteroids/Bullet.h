/*
 * Bullet.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <Jupiter.h>

class Bullet: public jupiter::IGameObject
{
public:
    Bullet(int screenWidth, int screenHeight, float x, float y, float angle);
    virtual ~Bullet();

    virtual void update(double elapsed);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const;
    virtual std::string getName() const;

    virtual jupiter::Rect getRect() const;

    virtual void collision(std::shared_ptr<IGameObject>);
    virtual bool removeMe() const;

private:
    std::shared_ptr<jupiter::Sprite> _bullet;

    glm::vec3 _vel, _pos;
    float _angle = 0.f;

    int _screenWidth = 0, _screenHeight = 0;

    jupiter::Rect _bulletRect;

    bool _remove = false;
};

#endif /* BULLET_H_ */
