/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#ifndef SWIG
#include <map>
#include <string>

#include <glm/glm.hpp>

#include <Jupiter/facade/Controller.h>
#endif

namespace jupiter
{

class Node
{
public:
#ifndef SWIG
    Node(const Controller&, std::map<std::string, Node> nodes);
#endif
    Node(const std::string& nodeName = {});
    virtual ~Node() = default;

    bool operator<(const Node&);
    bool operator>(const Node&);

#ifndef SWIG
private:
    glm::mat4 _model;
    std::map<std::string, Node> _nodes;
#endif
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
