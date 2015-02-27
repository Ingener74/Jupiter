/*
 * JsonGame.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JSONGAME_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JSONGAME_H_

#include "Game.h"

namespace jupiter {

class JsonGame: public Game {
public:
    JsonGame(const std::string& fileName);
    virtual ~JsonGame();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JSONGAME_H_ */
