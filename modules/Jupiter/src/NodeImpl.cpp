/*
 * NodeImpl.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <Jupiter/NodeImpl.h>

namespace jupiter
{

NodeImpl::NodeImpl(const std::string& name, bool isVisible, const glm::mat4& model, const Controller& controller,
        const std::map<std::string, Node>& nodes) :
        _name(name), _isVisible(isVisible), _model(model), _controller(controller), _nodes(nodes)
{
}

NodeImpl::~NodeImpl()
{
}

const std::string& NodeImpl::getName() const
{
    return _name;
}

bool NodeImpl::isVisible() const
{
    return _isVisible;
}

void NodeImpl::setVisible(bool visible)
{
    _isVisible = visible;
}

const glm::mat4& NodeImpl::getModel() const
{
    return _model;
}

void NodeImpl::setModel(const glm::mat4& model)
{
    _model = model;
}

Controller& NodeImpl::getController()
{
    return _controller;
}

std::map<std::string, Node>& NodeImpl::getNodes()
{
    return _nodes;
}

} /* namespace jupiter */
