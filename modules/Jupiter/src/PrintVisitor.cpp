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

void PrintVisitor::visit(Node* node) {
}

void PrintVisitor::visit(Sprite* sprite) {
}

void PrintVisitor::end() {
    cout << endl;
}

int PrintVisitor::calcTabs(Node* node) {
    int tabs = 0;
    auto parent = node->getParent();
    do {
        if (parent) {
            tabs++;
            parent = parent->getParent();
        }
    } while (parent);
    return tabs;
}

string PrintVisitor::tabs(int tab) {
    stringstream s;
    for(int i = 0; i < tab; ++i){
        s << "    ";
    }
    return s.str();
}

void PrintVisitor::visit(Body*) {
}

void PrintVisitor::visit(Camera*) {
}

void PrintVisitor::visit(SpriteBody*) {
}

void PrintVisitor::visit(Joint*) {
}

void PrintVisitor::visit(RevoluteJoint*) {
}

void PrintVisitor::visit(DistanceJoint*) {
}

void PrintVisitor::visit(RopeJoint*) {
}

void PrintVisitor::visit(MotorJoint*) {
}

void PrintVisitor::visit(GearJoint*) {
}

void PrintVisitor::visit(WheelJoint*) {
}

void PrintVisitor::visit(FrictionJoint*) {
}

void PrintVisitor::visit(MouseJoint*) {
}

void PrintVisitor::visit(PrismaticJoint*) {
}

void PrintVisitor::visit(PulleyJoint*) {
}

void PrintVisitor::visit(WeldJoint*) {
}

} /* namespace jupiter */
