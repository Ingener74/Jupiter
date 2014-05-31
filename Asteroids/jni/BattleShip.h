/*
 * BattleShip.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <Engine/Engine.h>

class BattleShip: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<BattleShip>;

    BattleShip(android_app * app, int screenWidth);
    virtual ~BattleShip();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();

    virtual void fire() throw ();

private:
    ndk_game::Sprite::Ptr _ship, _engineFire;

    bool _gas;
};

#endif /* BATTLESHIP_H_ */
