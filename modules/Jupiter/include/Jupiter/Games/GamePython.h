/*
 * GamePython.h
 *
 *  Created on: Nov 2, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GAMEPYTHON_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GAMEPYTHON_H_

#ifdef SWIG
#else
    #include <string>
#endif

#include "Jupiter/Game.h"

namespace jupiter {

class File;

class GamePython: public Game {
public:
    GamePython(File* script);
    GamePython(std::string const& script);
    virtual ~GamePython();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAMEPYTHON_H_ */
