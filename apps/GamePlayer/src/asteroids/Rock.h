/*
 * Rock.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef ROCK_H_
#define ROCK_H_

#include <Jupiter/Jupiter.h>

class Rock: public jupiter::IGameObject
{
public:
    using Ptr = std::shared_ptr<Rock>;

    static std::list<Rock::Ptr> createRock(int screenWidth, int screenHeight,
            std::shared_ptr<jupiter::ISoundEngine> soundEngine,
            glm::vec3 pos,
            bool second = false);

    virtual ~Rock();

    virtual void update(double elapsed) ;
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const ;
    virtual std::string getName() const ;

    virtual void collision(std::shared_ptr<IGameObject>) ;
    virtual bool removeMe() const ;

    virtual jupiter::Rect getRect() const;

    static void reset();

private:
    Rock(int screenWidth, int screenHeight,
            std::shared_ptr<jupiter::ISoundEngine> soundEngine,
            glm::vec3 pos,
            bool second);

//    android_app* _app;
    bool _second = false;

    std::shared_ptr<jupiter::Sprite> _rock;

    glm::vec3 _vel, _pos;
    float _angle = 0.f;

    int _screenWidth, _screenHeight;
    bool _crash = false;

    jupiter::Rect _rockRect;

    static int rocks;
    std::shared_ptr<jupiter::ISoundEngine> _soundEngine;
};

#endif /* ROCK_H_ */
