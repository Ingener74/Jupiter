/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Node.h"

#include "Jupiter/Game.h"

namespace jupiter {

using namespace std;
using namespace glm;

void Game::draw() {
    if (!_node)
        throw JupiterError("no root node");

    for (auto i : _visitors) {
        if (!i)
            throw JupiterError("bad visitor");
        i->begin();
        _node->accept(i);
        i->end();
    }
}

void Game::input() {
}

int Game::getWidth() const {
    return _width;
}

int Game::getHeight() const {
    return _height;
}

Game* Game::setHeight(int height) {
    _height = height;
    return this;
}

Game* Game::setWidth(int width) {
    _width = width;
    return this;
}

Game* Game::setRootNode(Node* node) {
    _node = node;
    return this;
}

Node* Game::getRootNode() {
    return _node;
}

Game* jupiter::Game::setVisitors(const std::list<NodeVisitor*>& visitors) {
    _visitors = visitors;
    return this;
}

const std::list<NodeVisitor*>& jupiter::Game::getVisitors() const {
    return _visitors;
}

Game* jupiter::Game::addVisitor(NodeVisitor* nodeVisitor) {
    _visitors.push_back(nodeVisitor);
    return this;
}

} /* namespace jupiter */
