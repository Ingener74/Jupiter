/*
 * JsonGameHolder.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include "JsonGameHolder.h"

namespace jupiter
{

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
}

} /* namespace jupiter */
