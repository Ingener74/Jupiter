/*
 * File-default.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: pavel
 */

#include "Jupiter/LinuxFileFactory.h"
#include "Jupiter/File.h"

namespace jupiter {

using namespace std;

static LinuxFileFactory fileFactory;

BufferFactory* File::factory = &fileFactory;
string File::base = "";

}  // namespace jupiter


