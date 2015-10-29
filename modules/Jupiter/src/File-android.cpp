/*
 * File-android.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: pavel
 */

#include "Jupiter/IO/AndroidAssetFactory.h"

namespace jupiter {

using namespace std;

AndroidAssetFactory androidAssetFactory { nullptr };

BufferFactory* File::_factory = &androidAssetFactory;
string File::_base = "";

}  // namespace jupiter

