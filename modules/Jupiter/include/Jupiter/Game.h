/*
 * Game.h
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_

#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Jupiter/RenderVisitor.h>
#include <Jupiter/Node.h>
#include <Jupiter/GameImpl.h>

namespace jupiter
{

class Game
{
public:
    Game();
    Game(const std::string& name);
    Game(const std::string& name, std::shared_ptr<GameImpl>);
    virtual ~Game();

    virtual void draw();

    virtual void input();

    virtual int32_t width() const;
    virtual int32_t height() const;

private:
    RenderVisitor render;
    std::shared_ptr<GameImpl> impl;
};

class JsonGameImpl: public GameImpl
{
public:
    JsonGameImpl(const std::string& gameFile) :
            GameImpl({}, 0, 0)
    {
    }
    virtual ~JsonGameImpl()
    {
    }
};

class DirectGameImpl: public GameImpl
{
public:
    DirectGameImpl(Node node) :
        GameImpl({}, 0, 0)
    {
    }
    virtual ~DirectGameImpl()
    {
    }
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */
