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
    Game(const std::string& gameFile);
    virtual ~Game();

    void draw();

    void input();

    int32_t width() const;
    int32_t height() const;

private:
    RenderVisitor _render;
    std::shared_ptr<GameImpl> _impl;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */
