/*
 * Life.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ingener
 */

#ifndef LIFE_H_
#define LIFE_H_

#include <Engine/IGameObject.h>

class Life: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<Life>;

    Life(int screenWidth, int screenHeight);
    virtual ~Life();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual void setLife(int);

private:
    ndk_game::Sprite::Ptr _life;

    float _w = 0.f, _x = 0.f, _y = 0.f;
    int _l = 3;
    void newLife();
};

#endif /* LIFE_H_ */
