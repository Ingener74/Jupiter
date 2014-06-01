/*
 * GameBuilder.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef GAMEBUILDER_H_
#define GAMEBUILDER_H_

#include <tuple>
#include <Engine/Engine.h>

class GameBuilder
{
public:
    using Ptr = std::shared_ptr<GameBuilder>;

    GameBuilder(void *savedState, int savedStateSize, int screenWidth, int screenHeight, android_app*);
    virtual ~GameBuilder();

    std::tuple<void *, size_t> saveGame();

    ndk_game::IDrawEngine::Ptr getEngine() const throw (std::runtime_error);

private:
    ndk_game::IDrawEngine::Ptr drawEngine;
    ndk_game::Scene::Ptr startScene, mainScene, winScene, failScene;

    int testSavedState;
};

#endif /* GAMEBUILDER_H_ */
