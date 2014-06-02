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

    BattleShip(android_app * app, int screenWidth, int screenHeight,
            std::weak_ptr<ndk_game::Scene> mainScene,
            std::weak_ptr<ndk_game::Scene> failScene,
            std::weak_ptr<ndk_game::IDrawEngine>,
            std::shared_ptr<ndk_game::ISoundEngine> soundEngine);

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
    android_app *_app;

    ndk_game::Sprite::Ptr _ship, _engineFire;

    bool _gas;

    float _mass;
    glm::vec3 _acc;
    glm::vec3 _vel;
    glm::vec3 _pos;
    float _angle;

    glm::vec3 _theForce;

    int _screenWidth, _screenHeight;

    std::weak_ptr<ndk_game::Scene> _parentScene, _failScene;
    std::weak_ptr<ndk_game::IDrawEngine> _engine;

    float _armed;
    int _life;
    float _shield;

    ndk_game::Rect _shipRect;
#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    std::shared_ptr<ndk_game::ISoundEngine> _soundEngine;

    ndk_game::Texture::Ptr _bulletTex;
};

#endif /* BATTLESHIP_H_ */
