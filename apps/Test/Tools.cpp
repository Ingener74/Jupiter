/*
 * Tools.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: pavel
 */

#include <iomanip>

#include "Tools.h"

using namespace std;
using namespace glm;

ostream& operator<<(ostream& out, const mat4& r){
    auto t = transpose(r);
    return out << endl <<
        "[" << setw(10) << t[0][0] << ", " << setw(10) << t[0][1] << ", " << setw(10) << t[0][2] << ", " << setw(10) << t[0][3] << ";" << endl <<
        " " << setw(10) << t[1][0] << ", " << setw(10) << t[1][1] << ", " << setw(10) << t[1][2] << ", " << setw(10) << t[1][3] << ";" << endl <<
        " " << setw(10) << t[2][0] << ", " << setw(10) << t[2][1] << ", " << setw(10) << t[2][2] << ", " << setw(10) << t[2][3] << ";" << endl <<
        " " << setw(10) << t[3][0] << ", " << setw(10) << t[3][1] << ", " << setw(10) << t[3][2] << ", " << setw(10) << t[3][3] << "]" << endl;
}
