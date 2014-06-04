/*
 * Game.h
 *
 *  Created on: Jun 4, 2014
 *      Author: pavel
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <map>

#include <Engine/Engine.h>

class Game
{
public:
    using Ptr = std::shared_ptr<Game>;

    static Ptr instance();
    static void reset();

    virtual ~Game();

    ndk_game::IDrawEngine::Ptr getEngine();

    ndk_game::Scene::Ptr getScene(const std::string& sceneName);
    ndk_game::Texture::Ptr getTexture(const std::string& textureFile);

    void startGame(android_app*, int screenWidth, int screenHeight);

    void newGame();

    void stopGame();

private:
    Game();

    android_app* _app;

    ndk_game::IDrawEngine::Ptr _engine;

    std::map<std::string, ndk_game::Scene::Ptr> _scenes;
    std::map<std::string, ndk_game::Texture::Ptr> _textures;

    static Ptr _self;
};

#endif /* GAME_H_ */
