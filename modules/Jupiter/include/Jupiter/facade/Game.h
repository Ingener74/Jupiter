/*
 * Game.h
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_

#ifndef SWIG
#include <string>
#endif

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
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */
