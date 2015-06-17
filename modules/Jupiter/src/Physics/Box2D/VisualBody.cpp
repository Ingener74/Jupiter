/*
 * VisualBody.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: pavel
 */

#include "Jupiter/Shader.h"
#include "Jupiter/VisualBody.h"

namespace jupiter {

VisualBody::VisualBody(Shader* program) :
    _shader(program) {
}

VisualBody::~VisualBody() {
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
