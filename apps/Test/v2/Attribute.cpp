/*
 * Attribute.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#include <iostream>

#include "Attribute.h"

using namespace std;

Attribute::Attribute(GLint attribute, string attributeName) :
    attribute(attribute), attributeName(attributeName) {
}

ostream& operator <<(ostream& out, const Attribute& r) {
    return out << r.attributeName << ": " << r.attribute;
}

