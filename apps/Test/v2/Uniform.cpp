/*
 * Uniform.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#include <iostream>

#include "Uniform.h"

using namespace std;

Uniform::Uniform(GLint uniform, string uniformName) :
    uniform(uniform), uniformName(uniformName) {
}

ostream& operator <<(ostream& out, const Uniform& r) {
    return out << r.uniformName << ": " << r.uniform;
}

