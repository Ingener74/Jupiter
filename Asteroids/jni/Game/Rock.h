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

    Rock(android_app * app, int screenWidth, int screenHeight);

    static ndk_game::Texture::Ptr loadTexture(android_app*);
#ifdef NDK_GAME_DEBUG
    static ndk_game::Texture::Ptr loadTextureRect(android_app *);
    static ndk_game::ISpriteLoader::Ptr createSpriteRect(const ndk_game::Rect&);
#endif

    virtual ~Rock();

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual void input(int x, int y) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

private:
//    std::list<ndk_game::Sprite::Ptr> _rockParts;
    ndk_game::Sprite::Ptr _rock;

    glm::vec3 _vel, _pos;
    float _angle;

    int _screenWidth, _screenHeight;

    ndk_game::Rect _rockRect;
#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif
};

#endif /* ROCK_H_ */
