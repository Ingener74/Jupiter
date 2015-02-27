/*
 * JsonSprite.h
 *
 *  Created on: 27 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JSONSPRITE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JSONSPRITE_H_

#include <boost/property_tree/ptree.hpp>

#include "Sprite.h"

namespace jupiter {

class JsonSprite: public Sprite {
public:
    JsonSprite(const boost::property_tree::ptree& node);
    virtual ~JsonSprite();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JSONSPRITE_H_ */
