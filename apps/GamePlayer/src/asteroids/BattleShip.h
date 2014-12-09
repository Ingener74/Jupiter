/*
 * BattleShip.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <Jupiter/DrawEngine.h>
#include <Life.h>

class BattleShip: public jupiter::IGameObject
{
public:
    using Ptr = std::shared_ptr<BattleShip>;

    BattleShip(int screenWidth, int screenHeight,
            Life::Ptr,
            std::shared_ptr<jupiter::ISoundEngine>,
            std::function<std::string()> gameLocation,
            std::function<std::shared_ptr<jupiter::Scene>(std::string)> getScene,
            std::function<void(std::shared_ptr<jupiter::Scene>)> sceneSelector);

    virtual ~BattleShip();

    virtual void update(double elapsed);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const ;
    virtual std::string getName() const ;

    virtual void collision(std::shared_ptr<jupiter::IGameObject>);

    virtual void fire();
    virtual void right();
    virtual void left();
    virtual void gas();

private:
    std::shared_ptr<jupiter::Sprite> _ship, _engineFire;

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

    jupiter::Rect _shipRect;

#ifdef NDK_GAME_DEBUG
    jupiter::Sprite::Ptr _rect;
#endif

    std::shared_ptr<jupiter::ISoundEngine> _soundEngine;
    Life::Ptr _lifeObj;

    std::function<std::string()> _gameLocation;
    std::function<std::shared_ptr<jupiter::Scene>(std::string)> _getScene;
    std::function<void(std::shared_ptr<jupiter::Scene>)> _setScene;
};

#endif /* BATTLESHIP_H_ */
