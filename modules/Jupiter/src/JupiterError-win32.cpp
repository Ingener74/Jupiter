/*
 * JupiterError-win32.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"

namespace jupiter {

using namespace std;

string JupiterError::backtrace() {
    return {};
}

#pragma message("Jupiter error default")

}  // namespace jupiter

