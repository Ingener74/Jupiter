/*
 * JSONNodeFactory.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include "JsonGameHolder.h"
#include <Jupiter/JSONNodeFactory.h>
#include <Jupiter/NodeImpl.h>

namespace jupiter
{

using namespace std;

JSONNodeFactory::JSONNodeFactory()
{
}

JSONNodeFactory::~JSONNodeFactory()
{
}

JSONNodeFactory::ProductImplPtr JSONNodeFactory::create(const std::string& nodeN)
{
    auto pt = JsonGameHolder::instance()->getGame();

    cout << __PRETTY_FUNCTION__ << " " << nodeN << endl;

    auto node = pt.get_child("node");

    auto name = node.get<string>("name");

    while(name != nodeN){

        cout << "while " << name << " != " << nodeN << endl;

        auto nodes = node.get_child_optional("nodes");
        if(nodes){
            cout << "have nodes" << endl;

            for(auto i: nodes.value()){

                auto child = i.second.get_child_optional("node");
                if(child){
                    auto n = child.value().get<string>("name");
                    cout << n << endl;

                    auto nn = "json:" + n;

                    cout << nn << endl;
                }
            }
        }
        else
            cout << "havn't nodes" << endl;
    }

    bool isVisible = true;
    auto isVisibleOptional = node.get_optional<bool>("visible");
    if(isVisibleOptional)
        isVisible = isVisibleOptional.value();

    glm::mat4 model{};
    auto modelOptional = node.get_child_optional("model");

    Controller controller;
    auto controllerOptional = node.get_optional<string>("controller");
    if(controllerOptional)
        controller = Controller{controllerOptional.value()};

    map<string, Node> nodes_;
    auto nodesOptional = node.get_child_optional("nodes");
    if (nodesOptional)
    {
        for(auto i: nodesOptional.value()){

            auto child = i.second.get_child_optional("node");
            if(child){
                auto n = child.value().get<string>("name");
                cout << n << endl;

                auto nn = "json:" + n;

                cout << nn << endl;

                nodes_[n] = Node{nn};
            }
        }
    }


    return make_shared<NodeImpl>(name, isVisible, model, controller, nodes_);
}

const boost::property_tree::ptree& JSONNodeFactory::findNode(boost::property_tree::ptree& pt, const std::string& name)
{
}

} /* namespace jupiter */
