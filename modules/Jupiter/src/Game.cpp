/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <boost/filesystem.hpp>

#include "Jupiter/Game.h"
#include "Jupiter/TextureBuilder.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;

Game::Game() {
}

Game::~Game() {
}

void Game::draw() {
    render.visit(node);
}

void Game::input() {
}

int Game::getWidth() const {
    return width;
}

int Game::getHeight() const {
    return height;
}

} /* namespace jupiter */
