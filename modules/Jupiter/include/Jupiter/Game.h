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

namespace jupiter
{

class Game
{
public:
    Game();
    virtual ~Game();

    virtual void draw();

    virtual void input();

    virtual int getWidth() const;
    virtual int getHeight() const;

private:
    RenderVisitor render;
    Node* node = nullptr;
    int width = 0;
    int height = 0;
};

class JsonGame: public Game
{
public:
    JsonGame(const std::string& gameFile)
    {
    }
    virtual ~JsonGame()
    {
    }
};

class DirectGame: public Game
{
public:
    DirectGame(Node* node)
    {
    }
    virtual ~DirectGame()
    {
    }
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */
