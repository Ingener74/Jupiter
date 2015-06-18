/*
 * VisualBody.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: pavel
 */

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Shader.h"
#include "Jupiter/Body.h"
#include "Jupiter/VisualBody.h"

namespace jupiter {

VisualBody::VisualBody(Shader* program) :
    _shader(program) {
}

VisualBody::VisualBody(VisualBody const& body) :
    Node(body) {
    *this = body;
}

VisualBody::~VisualBody() {
}

VisualBody* VisualBody::clone() {
    return new VisualBody(*this);
}

VisualBody* VisualBody::setParent(Node* node) {
    auto body = dynamic_cast<Body*>(node);
    jassert(body, "parent must be Physical Body");

    return this;
}

VisualBody* VisualBody::accept(NodeVisitor* nv) {
    jassert(nv, "visitor is nullptr");
    if (_visible) {
        nv->push(this);
        nv->visit(this);
        for (auto i : _nodes) {
            jassert(i, "invalid node");
            i->accept(nv);
        }
        nv->pop(this);
    }
    return this;
}

VisualBody* VisualBody::setProgram(Shader* shader) {
    jassert(shader, "invalid shader");
    _shader = shader;
    return this;
}

Shader* VisualBody::getProgram() {
    jassert(_shader, "no shader");
    return _shader.get();
}

} /* namespace jupiter */
