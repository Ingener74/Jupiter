/*
 * BattleShip.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <Engine/Engine.h>
#include <Game/Life.h>

class BattleShip: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<BattleShip>;

    BattleShip(int screenWidth, int screenHeight, Life::Ptr, ndk_game::ISoundEngine::Ptr);

    virtual ~BattleShip();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual void collision(IGameObject::Ptr) throw (std::runtime_error);

    virtual void fire() throw ();
    virtual void right() throw ();
    virtual void left() throw ();
    virtual void gas() throw ();

private:
    ndk_game::Sprite::Ptr _ship, _engineFire;

    bool _gas     = false;
    float _mass   = 10.f;
    glm::vec3 _acc;
    glm::vec3 _vel;
    glm::vec3 _pos;
    float _angle  = 0.f;
    float _armed  = 0.f;
    int _life     = 3;
    float _shield = 3.f;

    glm::vec3 _theForce;

    int _screenWidth, _screenHeight;

    ndk_game::Rect _shipRect;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    std::shared_ptr<ndk_game::ISoundEngine> _soundEngine;
    Life::Ptr _lifeObj;
};

#endif /* BATTLESHIP_H_ */
