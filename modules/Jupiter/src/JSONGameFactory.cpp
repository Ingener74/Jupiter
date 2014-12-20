/*
 * JSONGameFactory.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <boost/property_tree/json_parser.hpp>

#include <Jupiter/ResourceManager.h>
#include <Jupiter/GameImpl.h>
#include "JsonGameHolder.h"
#include <Jupiter/JSONGameFactory.h>

namespace jupiter
{

using namespace std;

JSONGameFactory::JSONGameFactory()
{
}

JSONGameFactory::~JSONGameFactory()
{
}

JSONGameFactory::ProductImplPtr JSONGameFactory::create(const std::string& game)
{
    boost::property_tree::ptree pt;

    boost::property_tree::json_parser::read_json(*ResourceManager::createResource(game), pt);

    int width  = pt.get<int>("resolution.width");
    int height = pt.get<int>("resolution.height");

    JsonGameHolder::instance()->setGame(pt);

    auto n = Node{"json:root"};

    return make_shared<GameImpl>(n, width, height);
}

} /* namespace jupiter */
