/*
 * Bullet.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <Engine/Engine.h>

class Bullet: public ndk_game::IGameObject
{
public:
    Bullet(android_app * app, int screenWidth, int screenHeight, float x, float y, float angle);
    virtual ~Bullet();

    static ndk_game::Texture::Ptr loadTexture(android_app *);
    static ndk_game::ISpriteLoader::Ptr createSprite(int w, int h);

#ifdef NDK_GAME_DEBUG
    static ndk_game::Texture::Ptr loadTextureRect(android_app *);
    static ndk_game::ISpriteLoader::Ptr createSpriteRect(const ndk_game::Rect&);
#endif

    virtual void update(double elapsed) throw (std::runtime_error);
    virtual std::list<ndk_game::Sprite::Ptr> getSprites() const throw ();
    virtual std::string getName() const throw ();

    virtual ndk_game::Rect getRect() const throw ();

    virtual bool removeMe() const throw ();

private:
    ndk_game::Sprite::Ptr _bullet;

    glm::vec3 _vel, _pos;
    float _angle;

    int _screenWidth, _screenHeight;

    ndk_game::Rect _bulletRect;
#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif
};

#endif /* BULLET_H_ */
