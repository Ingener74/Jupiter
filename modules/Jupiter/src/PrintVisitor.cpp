/*
 * PrintVisitor.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: ingener
 */

#include <iostream>

#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/PrintVisitor.h"

namespace jupiter {

using namespace std;

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::begin() {
}

void PrintVisitor::visit(Node* node) {
    int t = calcTabs(node);
    cout << tabs(t) << "node visible:   " << node->isVisible() << endl;
}

ostream& operator<<(ostream& out, const glm::mat4& r){
    return out << "["
        << r[0][0] << ", " << r[0][1] << ", " << r[0][2] << ", " << r[0][3] << "; "
        << r[1][0] << ", " << r[1][1] << ", " << r[1][2] << ", " << r[1][3] << "; "
        << r[2][0] << ", " << r[2][1] << ", " << r[2][2] << ", " << r[2][3] << "; "
        << r[3][0] << ", " << r[3][1] << ", " << r[3][2] << ", " << r[3][3] << "]";
}

void PrintVisitor::visit(Sprite* sprite) {
    int t = calcTabs(sprite);
    cout << tabs(t) << "sprite visible: " << sprite->isVisible() << endl <<
            tabs(t) << "sprite width:   " << sprite->getTexture()->getWidth() << " x " << sprite->getTexture()->getHeight() << endl <<
            tabs(t) << "sprite model:   " << sprite->getModel() << endl;
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

} /* namespace jupiter */

