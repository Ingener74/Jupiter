/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <boost/filesystem.hpp>

#include "Jupiter/Game.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;

void Game::draw() {
    assert(nullptr != node);
    assert(nullptr != render);

    node->accept(render);
    render->draw();
}

void Game::input() {
}

} /* namespace jupiter */
