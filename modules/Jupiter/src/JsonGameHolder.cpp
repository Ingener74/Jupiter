/*
 * JsonGameHolder.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include "JsonGameHolder.h"
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

std::shared_ptr<JsonGameHolder> JsonGameHolder::instance()
{
    static std::shared_ptr<JsonGameHolder> self(new JsonGameHolder);
    return self;
}

JsonGameHolder::~JsonGameHolder()
{
}

void JsonGameHolder::setGame(const boost::property_tree::ptree& pt)
{
    _pt = pt;
}

const boost::property_tree::ptree& JsonGameHolder::getGame() const
{
    return _pt;
}

JsonGameHolder::JsonGameHolder()
{
}

const boost::property_tree::ptree& jupiter::JsonGameHolder::findNode(const std::string& type, const std::string& name)
{
    auto node = _pt.get_child("node");

    auto nameName = node.get<string>("name");

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
}

} /* namespace jupiter */
