/*
 * Rock.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef ROCK_H_
#define ROCK_H_

#include <Engine/Engine.h>

class Rock: public ndk_game::IGameObject
{
public:
    using Ptr = std::shared_ptr<Rock>;

    static std::list<Rock::Ptr> createRock(int screenWidth, int screenHeight,
            std::shared_ptr<ndk_game::ISoundEngine> soundEngine,
            glm::vec3 pos,
            bool second = false);

    virtual ~Rock();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual void collision(IGameObject::Ptr) throw (std::runtime_error);
    virtual bool removeMe() const throw ();

    virtual ndk_game::Rect getRect() const;

    static void reset();

private:
    Rock(int screenWidth, int screenHeight,
            std::shared_ptr<ndk_game::ISoundEngine> soundEngine,
            glm::vec3 pos,
            bool second);

//    android_app* _app;
    bool _second = false;

    ndk_game::Sprite::Ptr _rock;

    glm::vec3 _vel, _pos;
    float _angle = 0.f;

    int _screenWidth, _screenHeight;
    bool _crash = false;

    ndk_game::Rect _rockRect;

    static int rocks;
    std::shared_ptr<ndk_game::ISoundEngine> _soundEngine;
};

#endif /* ROCK_H_ */
