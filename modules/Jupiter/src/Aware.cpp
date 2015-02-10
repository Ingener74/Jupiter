/*
 * Aware.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: pavel
 */

#include <iostream>

#include "Jupiter/Aware.h"

namespace jupiter
{

using namespace std;

Aware::Object::Object(const string& name): name(name)
{
}

void Aware::Object::setName(const string& name)
{
    Object::name = name;
}

const string& Aware::Object::getName() const
{
    return name;
}

void Aware::add(Object* so)
{
    if (so->getName().empty())
        throw JupiterError("Aware object name is empty");

    auto res = Register().insert({so->getName(), so});

    if (!res.second)
        throw JupiterError("Aware already have " + res.first->first);
    else
        cout << "added " << so->getName() << endl;
}

void Aware::remove(Object* so)
{
    Register().erase(so->getName());
    cout << "removed " << so->getName() << ", " << Register().size() << endl;
}

Aware::Reg& Aware::Register()
{
    static Reg reg;
    return reg;
}

} /* namespace jupiter */
