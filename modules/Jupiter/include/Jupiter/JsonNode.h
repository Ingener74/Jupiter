/*
 * JsonNode.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JSONNODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JSONNODE_H_

#include <boost/property_tree/ptree.hpp>

#include "Node.h"

namespace jupiter {

class JsonNode: public Node {
public:
    JsonNode(const boost::property_tree::ptree& node);
    virtual ~JsonNode();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JSONNODE_H_ */
