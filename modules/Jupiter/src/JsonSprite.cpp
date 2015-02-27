/*
 * JsonSprite.cpp
 *
 *  Created on: 27 февр. 2015 г.
 *      Author: pavel
 */

#include "Jupiter/JsonSprite.h"

namespace jupiter {

using namespace std;

JsonSprite::JsonSprite(const boost::property_tree::ptree& node) :
    Sprite(node.get<string>("name")) {
}

JsonSprite::~JsonSprite() {
}

} /* namespace jupiter */
