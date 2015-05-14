/*
 * NodeVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include "Jupiter/NodeVisitor.h"

namespace jupiter {

//using namespace std;

NodeVisitor::NodeVisitor() {
}

NodeVisitor::~NodeVisitor() {
}

void NodeVisitor::begin() {
}

void NodeVisitor::push(Node*) {
}

void NodeVisitor::pop() {
}

void NodeVisitor::visit(Node*) {
}

void NodeVisitor::visit(Sprite*) {
}

void NodeVisitor::visit(Box2dNode*) {
}

void NodeVisitor::end() {
}

} /* namespace jupiter */

