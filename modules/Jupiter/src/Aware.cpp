/*
 * Aware.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: pavel
 */

#include "Jupiter/Aware.h"

namespace jupiter {

using namespace std;

int Object::objects = 0;

Object::Object(const string& name) :
    name(name) {
    Aware::add(this);
    objects++;
}

Object::~Object() {
    Aware::remove(this);
    objects--;
}

void Object::setName(const string& name) {
    Object::name = name;
}

const string& Object::getName() const {
    return name;
}

size_t Aware::objectsCount() {
    return Register().size();
}

void Aware::release() {
    auto reg = Register();
    for (auto it = reg.begin(); it != reg.end(); ++it)
        if (it->second.first)
            delete it->second.second;
    reg.clear();
}

Aware::Reg& Aware::Register() {
    static Reg reg;
    return reg;
}

void Aware::add(Object* o) {
    if (o->getName().empty())
        throw JupiterError("Aware object name is empty");

    auto res = Register().insert( { o->getName(), { false, o } });

    if (!res.second) {
        if (res.first->second.first) {
            delete res.first->second.second;
            res.first->second.first = false;
        }
        res.first->second.second = o;
    }
}

void Aware::remove(Object* so) {
    Register().erase(so->getName());
}

void Aware::setCreated(Object* o) {
    Register().find(o->getName())->second.first = true;
}

} /* namespace jupiter */

