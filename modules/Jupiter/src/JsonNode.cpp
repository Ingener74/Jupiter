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

    if (auto nodes_ = node.get_child_optional("nodes"))
        for (auto i : nodes_.get())
            if (auto n = Aware::get<Node>(i.second.get_child("node").get<string>("name")))
                nodes.insert(NodePtr { n });
            else
                nodes.insert(NodePtr { Aware::create<JsonNode>(i.second.get_child("node")) });

    if (auto sprites_ = node.get_child_optional("sprites"))
        for (auto i : sprites_.get())
            if (auto n = Aware::get<Node>(i.second.get_child("sprite").get<string>("name")))
                nodes.insert(NodePtr { n });
            else
                nodes.insert(NodePtr { Aware::create<JsonNode>(i.second.get_child("sprite")) });
}

JsonNode::~JsonNode() {
}

} /* namespace jupiter */
