/*
 * File.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include "Jupiter/File.h"

namespace jupiter {

using namespace std;

unique_ptr<BufferFactory> File::factory;
string File::base = "";

}  // namespace jupiter
