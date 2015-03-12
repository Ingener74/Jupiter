/*
 * JsonNode.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include <boost/foreach.hpp>

#include "Jupiter/JsonNode.h"

namespace jupiter {

using namespace std;
using namespace boost::property_tree;

JsonNode::JsonNode(const ptree& node) :
        Node(node.get<std::string>("name")) {

    visible = node.get<bool>("visible");

    /*
     if (auto controller_ = node.get_optional<string>("controller")) {
     auto controllerFile = controller_.get();

     create lua or python controller
     }
     */

    if (auto nodes_ = node.get_child_optional("nodes")) {
        for (auto i : nodes_.get()) {
            if (auto json_node = i.second.get_child_optional("node"))
                createNode<JsonNode>(i.second.get_child("node"));
            if (auto json_sprite = i.second.get_child_optional("sprite"))
                createNode<JsonNode>(i.second.get_child("sprite"));
        }
    }
//    cout << name << " " << nodes.size() << endl;
}

JsonNode::~JsonNode() {
}

} /* namespace jupiter */
