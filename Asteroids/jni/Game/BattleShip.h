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

    BattleShip(android_app * app, int screenWidth, int screenHeight);
    virtual ~BattleShip();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual void fire() throw ();
    virtual void right() throw ();
    virtual void left() throw ();
    virtual void gas() throw ();

private:
    ndk_game::Sprite::Ptr _ship, _engineFire;

    bool _gas;

    glm::vec3 resistance(glm::vec3 velocity);

    float _mass;
    glm::vec3 _acc;
    glm::vec3 _vel;
    glm::vec3 _pos;

    glm::vec3 _theForce;

    int _screenWidth, _screenHeight;

    ndk_game::Rect _shipRect;
#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif
};

#endif /* BATTLESHIP_H_ */
