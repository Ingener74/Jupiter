/*
 * NodeVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include "Jupiter/NodeVisitor.h"

namespace jupiter {

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

void NodeVisitor::visit(Body*) {
}

void NodeVisitor::visit(Camera*) {
}

void NodeVisitor::end() {
}

void NodeVisitor::visit(SpriteBody*) {
}

void NodeVisitor::visit(Joint*) {
}

void NodeVisitor::visit(RevoluteJoint*) {
}

void NodeVisitor::visit(DistanceJoint*) {
}

void NodeVisitor::visit(RopeJoint*) {
}

void NodeVisitor::visit(MotorJoint*) {
}

void NodeVisitor::visit(GearJoint*) {
}

void NodeVisitor::visit(WheelJoint*) {
}

void NodeVisitor::visit(FrictionJoint*) {
}

void NodeVisitor::visit(MouseJoint*) {
}

void NodeVisitor::visit(PrismaticJoint*) {
}

void NodeVisitor::visit(PulleyJoint*) {
}

void NodeVisitor::visit(WeldJoint*) {
}

} /* namespace jupiter */
