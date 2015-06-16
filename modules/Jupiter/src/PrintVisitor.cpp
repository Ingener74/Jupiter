/*
 * PrintVisitor.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: ingener
 */

#include <sstream>
#include <iomanip>
#include <iostream>

#include "Jupiter/Tools.h"
#include "Jupiter/Texture.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/Game.h"
#include "Jupiter/PrintVisitor.h"

namespace jupiter {

using namespace std;
using namespace glm;

PrintVisitor::PrintVisitor(Game* game) :
    _game(game) {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::begin() {
    cout << *_game->getRootNode() << endl;
}

void PrintVisitor::end() {
    cout << endl;
}

} /* namespace jupiter */
