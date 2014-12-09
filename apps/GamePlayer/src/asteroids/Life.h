/*
 * Life.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ingener
 */

#ifndef LIFE_H_
#define LIFE_H_

#include <Jupiter/Jupiter.h>

class Life: public jupiter::IGameObject
{
public:
    using Ptr = std::shared_ptr<Life>;

    Life(int screenWidth, int screenHeight, std::function<std::string()> gameLocation);
    virtual ~Life();

    virtual void update(double elapsed);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const;
    virtual std::string getName() const;

    virtual void setLife(int);

private:
    std::shared_ptr<jupiter::Sprite> _life;

    float _w = 0.f, _x = 0.f, _y = 0.f;
    int _l = 3;
    void newLife();

    std::function<std::string()> _gameLocation;
};

#endif /* LIFE_H_ */
