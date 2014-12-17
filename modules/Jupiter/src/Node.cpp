/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <Jupiter/facade/Node.h>

namespace jupiter
{

jupiter::Node::Node(const Controller&, std::map<std::string, Node> nodes)
{
}

jupiter::Node::Node(const std::string& nodeName)
{
}

bool jupiter::Node::operator <(const Node& r)
{
    return _model[0][0] < r._model[0][0];
}

bool jupiter::Node::operator >(const Node& r)
{
    return _model[0][0] > r._model[0][0];
}

} /* namespace jupiter */
