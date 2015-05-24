/*
 * BackGround.h
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <list>
#include <functional>

#include <Jupiter.h>
#include <Tools.h>

class BackGround: public jupiter::IGameObject
{
public:
    BackGround();
    virtual ~BackGround() = default;

    virtual void update(double elapsed);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const ;
    virtual std::string getName() const ;

private:
    std::shared_ptr<jupiter::Sprite> background;
};

#endif /* BACKGROUND_H_ */
