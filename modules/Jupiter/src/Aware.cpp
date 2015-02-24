/*
 * Aware.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: pavel
 */

#include "Jupiter/Aware.h"

namespace jupiter {

using namespace std;

Aware::Object::Object(const string& name) :
    name(name) {
}

void Aware::Object::setName(const string& name) {
    Object::name = name;
}

const string& Aware::Object::getName() const {
    return name;
}

void Aware::add(Object* o) {
    add(o, false);
}

void Aware::remove(Object* so) {
    Register().erase(so->getName());
    cout << "removed " << so->getName() << ", " << Register().size() << endl;
}

void Aware::release() {
    auto reg = Register();
    for (auto it = reg.begin(); it != reg.end(); ++it)
        if (it->second.first)
            delete it->second.second;
}

Aware::Reg& Aware::Register() {
    static Reg reg;
    return reg;
}

void Aware::add(Object* o, Created c) {
    if (o->getName().empty())
        throw JupiterError("Aware object name is empty");

    auto res = Register().insert( { o->getName(), { c, o } });

    if (!res.second)
        throw JupiterError("Aware already have " + res.first->first);
    else
        cout << "added " << o->getName() << endl;
}

} /* namespace jupiter */

