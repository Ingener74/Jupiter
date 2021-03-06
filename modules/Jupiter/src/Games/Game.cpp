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
#include "Jupiter/KeyboardListener.h"

#include "Jupiter/Game.h"

namespace jupiter {

using namespace std;
using namespace glm;

void Game::draw() {
    jassert(_node, "no root node");

    for (auto i : _visitors) {
        jassert(i, "bad visitor");

        i->begin();
        _node->accept(i.get());
        i->end();
    }
}

void Game::keyboard(int keyCode) {
    for (auto i : _keyboardListeners) {
        jassert(i, "keyboard listener is invalid");
        i->key(keyCode);
    }
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
    jassert(_node, "no root node");
    return _node.get();
}

Game* jupiter::Game::setVisitors(const std::list<NodeVisitor*>& visitors) {
    jassert(!visitors.empty(), "invalid visitors list");

    for (auto i : visitors)
        _visitors.emplace_back(i->setGame(this));

    return this;
}

const std::list<Ref<NodeVisitor>>& jupiter::Game::getVisitors() const {
    return _visitors;
}

Game* jupiter::Game::addVisitor(NodeVisitor* visitor) {
    jassert(visitor, "visitor is invalid");
    visitor->setGame(this);
    _visitors.emplace_back(visitor);
    return this;
}

Game* Game::addKeyboardListener(KeyboardListener* listener) {
    jassert(listener, "listener is invalid");
    _keyboardListeners.emplace_back(listener);
    return this;
}

} /* namespace jupiter */
