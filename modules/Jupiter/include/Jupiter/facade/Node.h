/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#include <map>
#include <string>

#include <Jupiter/Controller.h>
#include <Jupiter/Sprite.h>

namespace jupiter
{

class Node
{
public:
    Node(Controller = {}, std::map<std::string, Sprite> sprites = {}, std::map<std::string, Node> nodes = {});
    virtual ~Node();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
