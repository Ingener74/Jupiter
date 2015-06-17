/*
 * NodeVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include "Jupiter/Game.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"

namespace jupiter {

Game* NodeVisitor::getGame() {
    jassert(_game, "no game");
    return _game;
}

NodeVisitor* NodeVisitor::setGame(Game* game) {
    jassert(game, "invalid game");
    _game = game;
    return this;
}

} /* namespace jupiter */
